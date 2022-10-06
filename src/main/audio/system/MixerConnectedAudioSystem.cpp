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

void MixerConnectedAudioSystem::notifyObservers(nonstd::any obj)
{
    
    if (!obj.has_value())
        return;
    
    if (obj.type() == typeid(weak_ptr<AudioDevice>))
    {
        auto device = nonstd::any_cast<weak_ptr<AudioDevice>>(obj).lock();
        
        if (device)
        {
            
            
            bool added = false;
            
            for (auto& ad : getAudioDevices())
            {
                if (ad.lock() == device)
                {
                    added = true;
                    break;
                }
            }
            
            auto outputs = device->getAudioOutputs();
            
            for (auto& output : outputs)
            {
                if (added)
                {
                    if (autoConnect)
                        createConnectionFrom(output);
                }
                else {
                    closeConnectionFrom(output);
                }
            }
        }
    }
    else if (obj.type() == typeid(weak_ptr<AudioOutput>))
    {
        auto output = nonstd::any_cast<std::weak_ptr<AudioOutput>>(obj).lock();
        
        if (output)
        {
            bool added = false;
            
            for (auto& ao : getAudioOutputs())
            {
                if (ao.lock() == output)
                {
                    added = true;
                    break;
                }
            }
            
            if (added)
            {
                if (autoConnect)
                    createConnectionFrom(output);
            }
            else {
                closeConnectionFrom(output);
            }
        }
    }
    
    DefaultAudioSystem::notifyObservers(obj);
}

vector<AudioConnection*>* MixerConnectedAudioSystem::getConnections()
{
    return &connections;
}

void MixerConnectedAudioSystem::createConnection(string fromPortName, string fromPortLocation, string toPortName, int flags)
{
    //MLOG("\nTrying to create connection from " + fromPortName + " to " + toPortName);
    auto from = getOutputPort(fromPortName, fromPortLocation);
    if (!from.lock()) {
        MLOG(fromPortName + " @ " + fromPortLocation + " does not exist");
        return;
    }
    auto to = mixer.lock()->getStrip(toPortName);
    if (to.lock() == nullptr) {
        MLOG(toPortName + " does not exist");
        return;
    }
    createConnection(from, to.lock().get(), flags);
}

void MixerConnectedAudioSystem::createConnection(std::weak_ptr<AudioOutput> from, ctoot::audio::mixer::AudioMixerStrip* to, int flags)
{
    //MLOG("\nTrying to create connection from " + from.lock()->getName() + " to " + to->getName());
    if (getConnectionFrom(from.lock()->getName(), from.lock()->getLocation()) != nullptr) {
        MLOG("Connection already exists");
        return;
    }
    AudioConnection* connection = new MixerInputConnection(this, from, to, flags);
    connections.push_back(connection);
    
    moduru::observer::Observable::notifyObservers();
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
                MLOG("Failed to create mixer strip " + name + " for " + nameAndLocation(output));
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
        MLOG("Failed to close connection from " + name + " @ " + location);
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
    
    moduru::observer::Observable::notifyObservers();
}

std::weak_ptr<AudioOutput> MixerConnectedAudioSystem::getOutputPort(string name, string location)
{
    for (auto& device : devices) {
        auto outputs = device.lock()->getAudioOutputs();
        for (auto& output : outputs) {
            if (name.compare(output.lock()->getName()) == 0 && location.compare(output.lock()->getLocation()) == 0) {
                return output;
            }
        }
    }
    MLOG("AudioOutput " + name + " @ " + location + " not found");
    return {};
}

string MixerConnectedAudioSystem::nameAndLocation(std::weak_ptr<AudioOutput> output)
{
    return output.lock()->getName() + " @ " + output.lock()->getLocation();
}

MixerConnectedAudioSystem::~MixerConnectedAudioSystem() {
    for (auto& c : connections) {
        if (c != nullptr) {
            c->close();
            delete c;
        }
    }
}
