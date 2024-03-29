#include <synth/BasicMidiSynth.hpp>

//#include <midi/MidiChannel.hpp>
#include <audio/system/AudioOutput.hpp>
#include <midi/message/ChannelMsg.hpp>
#include <midi/message/NoteMsg.hpp>
#include <midi/message/ShortMsg.hpp>
#include <midi/misc/Controller.hpp>
#include <synth/SynthChannel.hpp>

//#include <Logger.hpp>

using namespace ctoot::audio::system;
using namespace ctoot::synth;
using namespace ctoot::midi::core;
using namespace std;

BasicMidiSynth::BasicMidiSynth(string name)
	: AbstractMidiDevice(name)
{
	synthChannels = vector<shared_ptr<SynthChannel>>(16);
	for (auto& c : synthChannels)
		c = nullptr;
	addMidiInput(this);
}

void BasicMidiSynth::setLocation(string location)
{
    this->location = location;
}

string BasicMidiSynth::getName() {
	return AbstractMidiDevice::getName();
}

string BasicMidiSynth::getLocation()
{
    return location;
}

void BasicMidiSynth::setChannel(int chan, shared_ptr<SynthChannel> synthChannel)
{
	synthChannels[chan] = synthChannel;
}

vector<shared_ptr<SynthChannel>>* BasicMidiSynth::getChannels()
{
    return &synthChannels;
}

weak_ptr<SynthChannel> BasicMidiSynth::getChannel(int chan)
{
    return synthChannels[chan];
}

void BasicMidiSynth::transportChannel(ctoot::midi::core::MidiMessage* msg, SynthChannel* synthChannel)
{
	if (synthChannel == nullptr) return;
	if (ctoot::midi::message::NoteMsg::isNote(msg)) {
		auto pitch = ctoot::midi::message::NoteMsg::getPitch(msg);
		auto velocity = ctoot::midi::message::NoteMsg::getVelocity(msg);
		auto on = ctoot::midi::message::NoteMsg::isOn(msg);
		if (on) {
			synthChannel->noteOn(pitch, velocity);
		}
		else {
			synthChannel->noteOff(pitch, velocity);
		}
	}
	else {
		auto cmd = ctoot::midi::message::ChannelMsg::getCommand(msg);
		int controller;
		switch (cmd) {
		case ctoot::midi::message::ChannelMsg::PITCH_BEND:
			synthChannel->setPitchBend(ctoot::midi::message::ShortMsg::getData1and2(msg));
			break;
		case ctoot::midi::message::ChannelMsg::CONTROL_CHANGE:
			controller = ctoot::midi::message::ShortMsg::getData1(msg);
			if (controller == ctoot::midi::misc::Controller::ALL_CONTROLLERS_OFF) {
				synthChannel->resetAllControllers();
			}
			else if (controller == ctoot::midi::misc::Controller::ALL_NOTES_OFF) {
				synthChannel->allNotesOff();
			}
			else if (controller == ctoot::midi::misc::Controller::ALL_SOUND_OFF) {
				synthChannel->allSoundOff();
			}
			else {
				synthChannel->controlChange(controller, ctoot::midi::message::ShortMsg::getData2(msg));
			}
			break;
		case ctoot::midi::message::ChannelMsg::CHANNEL_PRESSURE:
			synthChannel->setChannelPressure(ctoot::midi::message::ShortMsg::getData1(msg));
			break;
		}
	}
}

weak_ptr<SynthChannel> BasicMidiSynth::mapChannel(int chan)
{
    return synthChannels[chan];
}

void BasicMidiSynth::transportChannel(ctoot::midi::core::MidiMessage* msg, int chan)
{
    transportChannel(msg, mapChannel(chan).lock().get());
}

void BasicMidiSynth::transport(ctoot::midi::core::MidiMessage* msg, int timestamp)
{
	if(ctoot::midi::message::ChannelMsg::isChannel(msg)) {
        transportChannel(msg, ctoot::midi::message::ChannelMsg::getChannel(msg));
    }
}

void BasicMidiSynth::closeMidi()
{
}

void BasicMidiSynth::addAudioOutput(std::weak_ptr<AudioOutput> output)
{
	//MLOG("BasicMidiSynth::addAudioOutput " + output.lock()->getName());
	audioOutputs.push_back(output);
    
    notifyObservers(output);
}

void BasicMidiSynth::removeAudioOutput(std::weak_ptr<AudioOutput> output)
{
	for (int i = 0; i < audioOutputs.size(); i++) {
		if (audioOutputs[i].lock() == output.lock()) {
			audioOutputs.erase(audioOutputs.begin() + i);
			break;
		}
	}
	
	notifyObservers(output);
}

vector<std::weak_ptr<AudioOutput>> BasicMidiSynth::getAudioOutputs()
{
    return audioOutputs;
}

vector<std::weak_ptr<AudioInput>> BasicMidiSynth::getAudioInputs()
{
	return {};
}

void BasicMidiSynth::closeAudio()
{
}

BasicMidiSynth::~BasicMidiSynth() {
}
