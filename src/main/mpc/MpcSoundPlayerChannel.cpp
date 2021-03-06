#include "MpcSoundPlayerChannel.hpp"

// ctootextensions
#include "MpcSoundPlayerControls.hpp"
#include "MpcMultiMidiSynth.hpp"
#include "MpcFaderControl.hpp"
#include "MpcMixerInterconnection.hpp"
#include "MpcVoice.hpp"
#include "MpcMuteInfo.hpp"

// mpc
#include <mpc/MpcNoteParameters.hpp>
#include <mpc/MpcProgram.hpp>
#include <mpc/MpcSampler.hpp>
#include <mpc/MpcStereoMixerChannel.hpp>
#include <mpc/MpcIndivFxMixerChannel.hpp>
#include <mpc/MpcMixerSetupGui.hpp>
#include <mpc/MpcSound.hpp>
#include <mpc/MpcMuteInfo.hpp>

// ctoot
#include <audio/core/MetaInfo.hpp>
#include <audio/core/AudioControlsChain.hpp>
#include <audio/mixer/AudioMixer.hpp>
#include <audio/mixer/AudioMixerStrip.hpp>
#include <audio/mixer/MainMixControls.hpp>
#include <audio/mixer/PanControl.hpp>
#include <audio/mixer/MixerControls.hpp>
#include <audio/server/AudioServer.hpp>
#include <control/CompoundControl.hpp>
#include <control/Control.hpp>

//#include <Mpc.hpp>

using namespace ctoot::mpc;
using namespace std;

MpcSoundPlayerChannel::MpcSoundPlayerChannel(weak_ptr<MpcSoundPlayerControls> controls)
{
	this->controls = controls;
	receivePgmChange = true;
	receiveMidiVolume = true;
	auto lControls = controls.lock();
	drumIndex = lControls->getDrumIndex();
	sampler = lControls->getSampler();
	mixer = lControls->getMixer();
	server = lControls->getServer();

	for (int i = 0; i < 64; i++)
	{
		stereoMixerChannels.push_back(make_shared<MpcStereoMixerChannel>());
        weakStereoMixerChannels.push_back(stereoMixerChannels.back());
		
        indivFxMixerChannels.push_back(make_shared<MpcIndivFxMixerChannel>());
        weakIndivFxMixerChannels.push_back(indivFxMixerChannels.back());
	}
}

void MpcSoundPlayerChannel::setProgram(int i)
{
	if (i < 0)
        return;
	
    if (!sampler.lock()->getMpcProgram(i).lock())
        return;
	
    programNumber = i;
	notifyObservers(string("pgm"));
}

int MpcSoundPlayerChannel::getProgram()
{
	return programNumber;
}

bool MpcSoundPlayerChannel::receivesPgmChange()
{
	return receivePgmChange;
}

void MpcSoundPlayerChannel::setReceivePgmChange(bool b)
{
	receivePgmChange = b;
	
	notifyObservers(string("receivepgmchange"));
}

bool MpcSoundPlayerChannel::receivesMidiVolume()
{
	return receiveMidiVolume;
}

void MpcSoundPlayerChannel::setReceiveMidiVolume(bool b)
{
	receiveMidiVolume = b;
	
	notifyObservers(string("receivemidivolume"));
}

int MpcSoundPlayerChannel::getLastReceivedMidiVolume()
{
	return lastReceivedMidiVolume;
}

void MpcSoundPlayerChannel::setLastReceivedMidiVolume(int volume)
{
	if (volume < 0 || volume > 127 || lastReceivedMidiVolume == volume)
		return;

	lastReceivedMidiVolume = volume;
}

void MpcSoundPlayerChannel::setLocation(string location)
{
}

void MpcSoundPlayerChannel::noteOn(int note, int velo)
{
	mpcNoteOn(-1, note, velo, 0, 64, 0, true);
}

void MpcSoundPlayerChannel::mpcNoteOn(int track, int note, int velo, int varType, int varValue, int frameOffset, bool firstGeneration)
{
	if (note < 35 || note > 98 || velo == 0)
		return;
	
	auto lSampler = sampler.lock();
	auto program = lSampler->getMpcProgram(programNumber);
	auto lProgram = program.lock();
	auto np = lProgram->getNoteParameters(note);

	checkForMutes(np);
	auto soundNumber = np->getSoundIndex();

	weak_ptr<MpcVoice> voice;
	auto lControls = controls.lock();
	
	for (auto& v : lControls->getMms().lock()->getVoices())
	{
		if (v.lock()->isFinished())
		{
			voice = v;
			break;
		}
	}

	if (soundNumber == -1 || !voice.lock())
		return;

	auto sound = lSampler->getMpcSound(soundNumber);

	auto smc = lProgram->getStereoMixerChannel(note - 35).lock();
	auto ifmc = lProgram->getIndivFxMixerChannel(note - 35).lock();

	bool sSrcDrum = controls.lock()->getMixerSetupGui()->isStereoMixSourceDrum();
	bool iSrcDrum = controls.lock()->getMixerSetupGui()->isIndivFxSourceDrum();

	if (sSrcDrum)
		smc = stereoMixerChannels[note - 35];

	if (iSrcDrum)
		ifmc = indivFxMixerChannels[note - 35];

	shared_ptr<ctoot::audio::mixer::AudioMixer> lMixer = mixer.lock();
	auto sc = lMixer->getMixerControls().lock()->getStripControls(to_string(voice.lock()->getStripNumber())).lock();
	
	// We set the FX send level.
	dynamic_pointer_cast<MpcFaderControl>(dynamic_pointer_cast<CompoundControl>(sc->find("FX#1").lock())
		->find("Level").lock())->setValue(static_cast<float>(ifmc->getFxSendLevel()));
	
	auto mmc = dynamic_pointer_cast<ctoot::audio::mixer::MainMixControls>(sc->find("Main").lock());
	dynamic_pointer_cast<ctoot::audio::mixer::PanControl>(mmc->find("Pan").lock())->setValue(static_cast<float>(smc->getPanning() / 100.0));
	dynamic_pointer_cast<ctoot::audio::fader::FaderControl>(mmc->find("Level").lock())->setValue(static_cast<float>(smc->getLevel()));

	sc = lMixer->getMixerControls().lock()->getStripControls(to_string(voice.lock()->getStripNumber() + 32)).lock();
	mmc = dynamic_pointer_cast<ctoot::audio::mixer::MainMixControls>(sc->find("Main").lock());

	//We make sure the voice strip duplicages that are used for mixing to ASSIGNABLE MIX OUT are not mixed into Main.
	auto faderControl = dynamic_pointer_cast<ctoot::audio::fader::FaderControl>(mmc->find("Level").lock());
	if (faderControl->getValue() != 0) faderControl->setValue(0);

	if (ifmc->getOutput() > 0)
	{
		if (sound.lock()->isMono())
		{
			if (ifmc->getOutput() % 2 == 1)
			{
				mixerConnections[voice.lock()->getStripNumber() - 1]->setLeftEnabled(true);
				mixerConnections[voice.lock()->getStripNumber() - 1]->setRightEnabled(false);
			}
			else
			{
				mixerConnections[voice.lock()->getStripNumber() - 1]->setLeftEnabled(false);
				mixerConnections[voice.lock()->getStripNumber() - 1]->setRightEnabled(true);
			}
		}
		else
		{
			mixerConnections[voice.lock()->getStripNumber() - 1]->setLeftEnabled(true);
			mixerConnections[voice.lock()->getStripNumber() - 1]->setRightEnabled(true);
		}
	}

	/*
	* We iterate through AUX#1 - #4 (aka ASSIGNABLE MIX OUT 1/2, 3/4, 5/6 and 7/8).
	* We silence the aux buses that are not in use by this voice.
	* We set the level for the MIX OUT that is in use, if any.
	*/
	int selectedAssignableMixOutPair = static_cast<int>(ceil((ifmc->getOutput() - 2) * 0.5));

	for (int i = 0; i < 4; i++)
	{
		auto auxControl = dynamic_pointer_cast<ctoot::control::CompoundControl>(sc->find("AUX#" + to_string(i + 1)).lock());
		auto auxLevel = dynamic_pointer_cast<MpcFaderControl>(auxControl->find("Level").lock());
	
		if (i == selectedAssignableMixOutPair)
		{
			auto value = static_cast<float>(ifmc->getVolumeIndividualOut());
			
			if (value != auxLevel->getValue())
				auxLevel->setValue(value);
		}
		else
		{
			if (auxLevel->getValue() != 0)
				auxLevel->setValue(0);
		}
	}

	startDecayForNote(note, 1);
    
	voice.lock()->init(track, velo, sound, note, np, varType, varValue, note, drumIndex, frameOffset, true);

	if (firstGeneration)
	{
		if (np->getSoundGenerationMode() == 1)
		{
			int optA = np->getOptionalNoteA();
			int optB = np->getOptionalNoteB();
			
			if (optA != 34)
			{
				mpcNoteOn(track, optA, velo, varType, varValue, frameOffset, false);
				simultA[note] = optA;
			}

			if (optB != 34)
			{
				mpcNoteOn(track, optB, velo, varType, varValue, frameOffset, false);
				simultB[note] = optB;
			}
		}
	}
}

void MpcSoundPlayerChannel::checkForMutes(ctoot::mpc::MpcNoteParameters* np)
{
	if (np->getMuteAssignA() != 34 || np->getMuteAssignB() != 34)
	{
		for (auto& v : controls.lock()->getMms().lock()->getVoices())
		{
			if (v.lock()->isFinished() || v.lock()->getMuteInfo() == nullptr)
				continue;
			
			if (v.lock()->getMuteInfo()->muteMe(np->getMuteAssignA(), drumIndex)
				|| v.lock()->getMuteInfo()->muteMe(np->getMuteAssignB(), drumIndex))
			{
				v.lock()->startDecay();
			}
		}
	}
}

void MpcSoundPlayerChannel::startDecayForNote(const int note, const int voiceOverlapMode)
{
    for (auto& v : controls.lock()->getMms().lock()->getVoices())
    {
        if (v.lock()->getNote() == note
            && v.lock()->getVoiceOverlap() == voiceOverlapMode
            && !v.lock()->isDecaying()
            && drumIndex == v.lock()->getMuteInfo()->getDrum())
        {
            v.lock()->startDecay();
            break;
        }
    }
}

void MpcSoundPlayerChannel::noteOff(int note)
{
	mpcNoteOff(note, 0);
}

void MpcSoundPlayerChannel::allNotesOff()
{
}

void MpcSoundPlayerChannel::allSoundOff()
{
	for (auto& voice : controls.lock()->getMms().lock()->getVoices())
	{
		if (voice.lock()->isFinished())
			continue;
		
		voice.lock()->startDecay();
	}
}

void MpcSoundPlayerChannel::allSoundOff(int frameOffset)
{
	for (auto& voice : controls.lock()->getMms().lock()->getVoices())
	{
		if (voice.lock()->isFinished())
			continue;
		
		voice.lock()->startDecay(frameOffset);
	}
}

void MpcSoundPlayerChannel::connectVoices()
{
	auto lMixer = mixer.lock();
	for (auto j = 0; j < 32; j++)
	{
		auto ams1 = lMixer->getStrip(to_string(j + 1)).lock();
		auto voice = controls.lock()->getMms().lock()->getVoices()[j];
		ams1->setInputProcess(voice);
		auto mi = new MpcMixerInterconnection("con" + to_string(j), server);
		ams1->setDirectOutputProcess(mi->getInputProcess());
		auto ams2 = lMixer->getStrip(to_string(j + 1 + 32)).lock();
		ams2->setInputProcess(mi->getOutputProcess());
		mixerConnections.push_back(mi);
	}
}

weak_ptr<ctoot::audio::core::MetaInfo> MpcSoundPlayerChannel::getInfo()
{
	return weak_ptr<ctoot::audio::core::MetaInfo>();
}

vector<weak_ptr<ctoot::mpc::MpcStereoMixerChannel>> MpcSoundPlayerChannel::getStereoMixerChannels()
{
    return weakStereoMixerChannels;
}

vector<weak_ptr<ctoot::mpc::MpcIndivFxMixerChannel>> MpcSoundPlayerChannel::getIndivFxMixerChannels()
{
	return weakIndivFxMixerChannels;
}

int MpcSoundPlayerChannel::getDrumNumber()
{
	return drumIndex;
}

void MpcSoundPlayerChannel::mpcNoteOff(int note, int frameOffset)
{
	if (note < 35 || note > 98)
		return;

	startDecayForNote(note, 2, frameOffset);
    
	std::map<int, int>::iterator it = simultA.find(note);

	if (it != simultA.end())
	{
		startDecayForNote(simultA[note], 2);
		simultA.erase(it);
	}
	
	it = simultB.find(note);
	
	if (it != simultB.end())
	{
		startDecayForNote(simultB[note], 2);
		simultB.erase(it);
	}
}

void MpcSoundPlayerChannel::startDecayForNote(const int note, const int voiceOverlapMode, const int frameOffset)
{
	for (auto& v : controls.lock()->getMms().lock()->getVoices())
	{
		if (v.lock()->getNote() == note
			&& v.lock()->getVoiceOverlap() == voiceOverlapMode
			&& !v.lock()->isDecaying()
			&& drumIndex == v.lock()->getMuteInfo()->getDrum())
		{
			v.lock()->startDecay(frameOffset);
			break;
		}
	}
}

MpcSoundPlayerChannel::~MpcSoundPlayerChannel() {
	for (auto& m : mixerConnections)
	{
		if (m != nullptr)
			delete m;
	}
}
