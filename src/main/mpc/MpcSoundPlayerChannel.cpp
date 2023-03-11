#include "MpcSoundPlayerChannel.hpp"

// ctootextensions
#include "MpcSoundPlayerControls.hpp"
#include "MpcMultiMidiSynth.hpp"
#include "MpcFaderControl.hpp"
#include "MpcMixerInterconnection.hpp"
#include "MpcVoice.hpp"

// mpc
#include <mpc/MpcNoteParameters.hpp>
#include <mpc/MpcProgram.hpp>
#include <mpc/MpcSampler.hpp>
#include <mpc/MpcStereoMixerChannel.hpp>
#include <mpc/MpcIndivFxMixerChannel.hpp>
#include <mpc/MpcMixerSetupGui.hpp>
#include <mpc/MpcSound.hpp>

// ctoot
#include <audio/mixer/AudioMixerStrip.hpp>
#include <audio/mixer/MainMixControls.hpp>
#include <audio/mixer/PanControl.hpp>
#include <control/CompoundControl.hpp>
#include <control/Control.hpp>

using namespace ctoot::mpc;
using namespace std;

MpcSoundPlayerChannel::MpcSoundPlayerChannel(weak_ptr<MpcSoundPlayerControls> controlsToUse)
{
	controls = controlsToUse.lock();
	receivePgmChange = true;
	receiveMidiVolume = true;

	drumIndex = controls->getDrumIndex();
	sampler = controls->getSampler().lock();
	mixer = controls->getMixer().lock();
	server = controls->getServer();

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

    if (!sampler->getMpcProgram(i))
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
	mpcNoteOn(note, velo, 0, 64, 0, true, -1, -1);
}

void MpcSoundPlayerChannel::mpcNoteOn(int note, int velo, int varType, int varValue, int frameOffset, bool firstGeneration, int startTick, int durationFrames)
{
	if (note < 35 || note > 98 || velo == 0)
		return;

	auto program = sampler->getMpcProgram(programNumber);
	auto np = program->getNoteParameters(note);

	checkForMutes(np);
	auto soundNumber = np->getSoundIndex();

	shared_ptr<MpcVoice> voice;

	for (auto& v : controls->getMms().lock()->getVoices())
	{
		if (v.lock()->isFinished())
		{
			voice = v.lock();
			break;
		}
	}

	if (soundNumber == -1 || !voice)
		return;

	auto sound = sampler->getMpcSound(soundNumber);

	auto smc = program->getStereoMixerChannel(note - 35).lock();
	auto ifmc = program->getIndivFxMixerChannel(note - 35).lock();

	bool sSrcDrum = controls->getMixerSetupGui()->isStereoMixSourceDrum();
	bool iSrcDrum = controls->getMixerSetupGui()->isIndivFxSourceDrum();

	if (sSrcDrum)
		smc = stereoMixerChannels[note - 35];

	if (iSrcDrum)
		ifmc = indivFxMixerChannels[note - 35];

    auto mixerControls = mixer->getMixerControls().lock();

	auto sc = mixerControls->getStripControls(to_string(voice->getStripNumber())).lock();

	auto mmc = dynamic_pointer_cast<ctoot::audio::mixer::MainMixControls>(sc->find("Main").lock());
	dynamic_pointer_cast<ctoot::audio::mixer::PanControl>(mmc->find("Pan").lock())->setValue(static_cast<float>(smc->getPanning() / 100.0));
	dynamic_pointer_cast<ctoot::audio::fader::FaderControl>(mmc->find("Level").lock())->setValue(static_cast<float>(smc->getLevel()));

	sc = mixerControls->getStripControls(to_string(voice->getStripNumber() + 32)).lock();
	mmc = dynamic_pointer_cast<ctoot::audio::mixer::MainMixControls>(sc->find("Main").lock());

	//We make sure the voice strip duplicages that are used for mixing to ASSIGNABLE MIX OUT are not mixed into Main.
	auto faderControl = dynamic_pointer_cast<ctoot::audio::fader::FaderControl>(mmc->find("Level").lock());
	if (faderControl->getValue() != 0) faderControl->setValue(0);

	if (ifmc->getOutput() > 0)
	{
		if (sound->isMono())
		{
			if (ifmc->getOutput() % 2 == 1)
			{
				mixerConnections[voice->getStripNumber() - 1]->setLeftEnabled(true);
				mixerConnections[voice->getStripNumber() - 1]->setRightEnabled(false);
			}
			else
			{
				mixerConnections[voice->getStripNumber() - 1]->setLeftEnabled(false);
				mixerConnections[voice->getStripNumber() - 1]->setRightEnabled(true);
			}
		}
		else
		{
			mixerConnections[voice->getStripNumber() - 1]->setLeftEnabled(true);
			mixerConnections[voice->getStripNumber() - 1]->setRightEnabled(true);
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

    if (np->getVoiceOverlap() == VoiceOverlapMode::MONO)
    {
        stopMonoOrPolyVoiceWithSameNoteParameters(np, note);
    }

	voice->init(velo, sound, note, np, varType, varValue, note, drumIndex, frameOffset, true, startTick, durationFrames);

	if (firstGeneration)
	{
		if (np->getSoundGenerationMode() == 1)
		{
			int optA = np->getOptionalNoteA();
			int optB = np->getOptionalNoteB();

			if (optA != 34)
			{
				mpcNoteOn(optA, velo, varType, varValue, frameOffset, false, startTick, durationFrames);
				simultA[note] = optA;
			}

			if (optB != 34)
			{
				mpcNoteOn(optB, velo, varType, varValue, frameOffset, false, startTick, durationFrames);
				simultB[note] = optB;
			}
		}
	}
}

void MpcSoundPlayerChannel::checkForMutes(ctoot::mpc::MpcNoteParameters* np)
{
	if (np->getMuteAssignA() != 34 || np->getMuteAssignB() != 34)
	{
		for (auto& v : controls->getMms().lock()->getVoices())
		{
			if (v.lock()->isFinished())
				continue;

			if (v.lock()->getMuteInfo().shouldMute(np->getMuteAssignA(), drumIndex)
				|| v.lock()->getMuteInfo().shouldMute(np->getMuteAssignB(), drumIndex))
			{
				v.lock()->startDecay();
			}
		}
	}
}

void MpcSoundPlayerChannel::noteOff(int note)
{
	mpcNoteOff(note, 0, -1);
}

void MpcSoundPlayerChannel::allNotesOff()
{
    for (int note = 35; note <= 98; note++)
    {
        for (auto& v : controls->getMms().lock()->getVoices())
        {
            auto voice = v.lock();

            if (!voice->isFinished()
                && voice->getNote() == note
                && voice->getVoiceOverlap() == VoiceOverlapMode::NOTE_OFF
                && !voice->isDecaying()
                && drumIndex == voice->getMuteInfo().getDrum())
            {
                voice->startDecay(0);
                break;
            }
        }
    }
}

void MpcSoundPlayerChannel::allSoundOff()
{
	for (auto& voice : controls->getMms().lock()->getVoices())
	{
		if (voice.lock()->isFinished())
			continue;

		voice.lock()->startDecay();
	}
}

void MpcSoundPlayerChannel::allSoundOff(int frameOffset)
{
	for (auto& voice : controls->getMms().lock()->getVoices())
	{
		if (voice.lock()->isFinished())
			continue;

		voice.lock()->startDecay(frameOffset);
	}
}

void MpcSoundPlayerChannel::connectVoices()
{
	for (auto j = 0; j < 32; j++)
	{
		auto ams1 = mixer->getStrip(to_string(j + 1)).lock();
		auto voice = controls->getMms().lock()->getVoices()[j];
		ams1->setInputProcess(voice);
		auto mi = new MpcMixerInterconnection("con" + to_string(j), server);
		ams1->setDirectOutputProcess(mi->getInputProcess());
		auto ams2 = mixer->getStrip(to_string(j + 1 + 32)).lock();
		ams2->setInputProcess(mi->getOutputProcess());
		mixerConnections.push_back(mi);
	}
}

vector<weak_ptr<ctoot::mpc::MpcStereoMixerChannel>> MpcSoundPlayerChannel::getStereoMixerChannels()
{
    return weakStereoMixerChannels;
}

vector<weak_ptr<ctoot::mpc::MpcIndivFxMixerChannel>> MpcSoundPlayerChannel::getIndivFxMixerChannels()
{
	return weakIndivFxMixerChannels;
}

void MpcSoundPlayerChannel::mpcNoteOff(int note, int frameOffset, int noteOnStartTick)
{
	if (note < 35 || note > 98)
		return;

    startDecayForNote(note, frameOffset, noteOnStartTick);

	auto it = simultA.find(note);

	if (it != simultA.end())
	{
		startDecayForNote(simultA[note], frameOffset, noteOnStartTick);
		simultA.erase(it);
	}

	it = simultB.find(note);

	if (it != simultB.end())
	{
		startDecayForNote(simultB[note], frameOffset, noteOnStartTick);
		simultB.erase(it);
	}
}

void MpcSoundPlayerChannel::startDecayForNote(const int note, const int frameOffset, const int noteOnStartTick)
{
    for (auto& v : controls->getMms().lock()->getVoices())
	{
        auto voice = v.lock();

		if (!voice->isFinished()
            && voice->getStartTick() == noteOnStartTick
            && voice->getNote() == note
			&& voice->getVoiceOverlap() == VoiceOverlapMode::NOTE_OFF
			&& !voice->isDecaying()
			&& drumIndex == voice->getMuteInfo().getDrum())
		{
            voice->startDecay(frameOffset);
			break;
		}
	}
}

void MpcSoundPlayerChannel::stopMonoOrPolyVoiceWithSameNoteParameters(
        ctoot::mpc::MpcNoteParameters* noteParameters, int note)
{
    for (auto& v : controls->getMms().lock()->getVoices())
    {
        auto voice = v.lock();

        if (voice->getNoteParameters() == noteParameters) {
            if (voice->getNote() == note) {
                if (voice->getVoiceOverlap() == VoiceOverlapMode::POLY ||
                    voice->getVoiceOverlap() == VoiceOverlapMode::MONO)
                {
                    voice->startDecay();
                }
            }
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
