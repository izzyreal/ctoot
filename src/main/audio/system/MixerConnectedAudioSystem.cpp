#include "MixerConnectedAudioSystem.hpp"

#include <audio/core/AudioControlsChain.hpp>
#include <audio/mixer/AudioMixer.hpp>
#include <audio/mixer/AudioMixerStrip.hpp>
#include <audio/mixer/MixerControlsIds.hpp>
#include <audio/system/AudioConnection.hpp>
#include <audio/system/AudioDevice.hpp>
#include <audio/system/AudioOutput.hpp>
#include <audio/system/MixerInputConnection.hpp>

using namespace ctoot::audio::system;
using namespace std;

MixerConnectedAudioSystem::MixerConnectedAudioSystem(shared_ptr<ctoot::audio::mixer::AudioMixer> mixer) 
{
    this->mixer = mixer;
    mixerControls = mixer->getMixerControls();
}

vector<AudioConnection*>* MixerConnectedAudioSystem::getConnections()
{
    return &connections;
}

void MixerConnectedAudioSystem::createConnection(std::weak_ptr<AudioOutput> from, ctoot::audio::mixer::AudioMixerStrip* to, int flags)
{
    if (getConnectionFrom(from.lock()->getName(), from.lock()->getLocation()) != nullptr)
    {
        return;
    }

    AudioConnection* connection = new MixerInputConnection(this, from, to, flags);
    connections.push_back(connection);
}

AudioConnection* MixerConnectedAudioSystem::getConnectionFrom(string from, string fromLocation)
{
    for (auto& c : connections) {
        if (c->getOutputName().compare(from) == 0 && c->getOutputLocation().compare(fromLocation) == 0) {
            return c;
        }
    }
    return nullptr;
}

void MixerConnectedAudioSystem::createConnectionFrom(std::weak_ptr<AudioOutput> output)
{
    shared_ptr<ctoot::audio::core::AudioControlsChain> stripControls;
    shared_ptr<ctoot::audio::core::AudioControlsChain> namedControls;
    try {
        auto strip = mixer.lock()->getUnusedChannelStrip().lock();
        if (!strip) {
            auto i = -1;
            auto max = 1 + mixerControls.lock()->getControls().size();
            string name;
            do {
                stripControls = mixerControls.lock()->getStripControls(ctoot::audio::mixer::MixerControlsIds::CHANNEL_STRIP, ++i).lock();
                name = to_string(i + 1);
                namedControls = mixerControls.lock()->getStripControls(name).lock();
            } while (stripControls && namedControls && i < max);
            mixerControls.lock()->createStripControls(ctoot::audio::mixer::MixerControlsIds::CHANNEL_STRIP, i, name);
            strip = mixer.lock()->getStrip(name).lock();
            if (!strip) {
                return;
            }
        }
        createConnection(output, strip.get(), 0);
    }
    catch (const exception& e) {
        printf("%s", e.what());
    }
}

void MixerConnectedAudioSystem::closeConnectionFrom(std::weak_ptr<AudioOutput> output)
{
    auto name = output.lock()->getName();
    auto location = output.lock()->getLocation();
    auto connection = getConnectionFrom(name, location);
    if (connection == nullptr) {
        return;
    }
    closeConnection(connection);
}

void MixerConnectedAudioSystem::closeConnection(AudioConnection* connection)
{
    connection->close();
    int index = 0;
    for (auto& c : connections) {
        if (c == connection)
            break;
        index++;
    }
    if (index >= connections.size()) return;
    connections.erase(connections.begin() + index);
}

MixerConnectedAudioSystem::~MixerConnectedAudioSystem() {
    for (auto& c : connections) {
        if (c != nullptr) {
            c->close();
            delete c;
        }
    }
}
