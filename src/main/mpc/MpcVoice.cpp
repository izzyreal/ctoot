#include <mpc/MpcVoice.hpp>

#include <mpc/MpcNoteParameters.hpp>
#include <mpc/MpcSound.hpp>

#include <mpc/MpcEnvelopeControls.hpp>
#include <mpc/MpcEnvelopeGenerator.hpp>
#include <mpc/MpcSoundPlayerChannel.hpp>
#include <mpc/MpcMuteInfo.hpp>

#include <audio/core/AudioBuffer.hpp>
#include <audio/core/ChannelFormat.hpp>
#include <control/BooleanControl.hpp>
#include <control/Control.hpp>
#include <control/FloatControl.hpp>
#include <synth/modules/filter/StateVariableFilter.hpp>
#include <synth/modules/filter/StateVariableFilterControls.hpp>

#include <cmath>

#include <file/File.hpp>

#ifdef __linux__
#include <climits>
#endif

using namespace ctoot::mpc;

MpcVoice::MpcVoice(int stripNumber, bool basic)
{
	EMPTY_FRAME = std::vector<float>{ 0.f, 0.f };
	tempFrame = std::vector<float>{ 0.f, 0.f };
	muteInfo = new MpcMuteInfo();
	this->stripNumber = stripNumber;
	this->basic = basic;
	staticEnvControls = new ctoot::mpc::MpcEnvelopeControls(0, "StaticAmpEnv", AMPENV_OFFSET);
	staticEnvControls->setSampleRate(sampleRate);
	staticEnv = new ctoot::mpc::MpcEnvelopeGenerator(staticEnvControls);
	sattack = std::dynamic_pointer_cast<ctoot::control::FloatControl>(staticEnvControls->getControls()[ATTACK_INDEX].lock()).get();
	shold = std::dynamic_pointer_cast<ctoot::control::FloatControl>(staticEnvControls->getControls()[HOLD_INDEX].lock()).get();
	sdecay = std::dynamic_pointer_cast<ctoot::control::FloatControl>(staticEnvControls->getControls()[DECAY_INDEX].lock()).get();

	timeRatio = 5.46f * (44100.0 / sampleRate);

	if (!basic) {
		ampEnvControls = new ctoot::mpc::MpcEnvelopeControls(0, "AmpEnv", AMPENV_OFFSET);
		ampEnvControls->setSampleRate(sampleRate);
		filterEnvControls = new ctoot::mpc::MpcEnvelopeControls(0, "StaticAmpEnv", AMPENV_OFFSET);
		filterEnvControls->setSampleRate(sampleRate);
		ampEnv = new ctoot::mpc::MpcEnvelopeGenerator(ampEnvControls);
		filterEnv = new ctoot::mpc::MpcEnvelopeGenerator(filterEnvControls);
		svfControls = new ctoot::synth::modules::filter::StateVariableFilterControls(0, "Filter", SVF_OFFSET);
		svfControls->setSampleRate(sampleRate);
		svfControls->createControls();
		svf0 = new ctoot::synth::modules::filter::StateVariableFilter(svfControls);
		svf1 = new ctoot::synth::modules::filter::StateVariableFilter(svfControls);
		fattack = std::dynamic_pointer_cast<ctoot::control::FloatControl>(filterEnvControls->getControls()[ATTACK_INDEX].lock()).get();
		fhold = std::dynamic_pointer_cast<ctoot::control::FloatControl>(filterEnvControls->getControls()[HOLD_INDEX].lock()).get();
		fdecay = std::dynamic_pointer_cast<ctoot::control::FloatControl>(filterEnvControls->getControls()[DECAY_INDEX].lock()).get();
		attack = std::dynamic_pointer_cast<ctoot::control::FloatControl>(ampEnvControls->getControls()[ATTACK_INDEX].lock()).get();
		hold = std::dynamic_pointer_cast<ctoot::control::FloatControl>(ampEnvControls->getControls()[HOLD_INDEX].lock()).get();
		decay = std::dynamic_pointer_cast<ctoot::control::FloatControl>(ampEnvControls->getControls()[DECAY_INDEX].lock()).get();
		reso = std::dynamic_pointer_cast<ctoot::control::FloatControl>(svfControls->getControls()[RESO_INDEX].lock()).get();
		mix = std::dynamic_pointer_cast<ctoot::control::FloatControl>(svfControls->getControls()[MIX_INDEX].lock()).get();
		bandpass = std::dynamic_pointer_cast<ctoot::control::BooleanControl>(svfControls->getControls()[BANDPASS_INDEX].lock()).get();
	}
}

const float MpcVoice::STATIC_ATTACK_LENGTH{ 10.92f };
const float MpcVoice::STATIC_DECAY_LENGTH{ 109.2f };
const int MpcVoice::MAX_ATTACK_LENGTH_MS;
const int MpcVoice::MAX_DECAY_LENGTH_MS;
const int MpcVoice::MAX_ATTACK_LENGTH_SAMPLES;
const int MpcVoice::MAX_DECAY_LENGTH_SAMPLES;
const int MpcVoice::ATTACK_INDEX;
const int MpcVoice::HOLD_INDEX;
const int MpcVoice::DECAY_INDEX;
const int MpcVoice::RESO_INDEX;
const int MpcVoice::MIX_INDEX;
const int MpcVoice::BANDPASS_INDEX;
const int MpcVoice::SVF_OFFSET;
const int MpcVoice::AMPENV_OFFSET;

void MpcVoice::init(
	int track,
	int velocity,
	int padNumber,
	std::weak_ptr<ctoot::mpc::MpcSound> oscVars,
	ctoot::mpc::MpcNoteParameters* np,
	int varType,
	int varValue,
	int muteNote,
	int muteDrum,
	int frameOffset,
	bool enableEnvs)
{
	this->enableEnvs = enableEnvs;
	this->frameOffset = frameOffset;
	this->track = track;
	this->np = np;
	this->padNumber = padNumber;
	this->oscVars = oscVars;
	this->varType = varType;
	this->varValue = varValue;

	finished = false;
	readyToPlay = false;
	staticDecay = false;
	muteInfo->setNote(muteNote);
	muteInfo->setDrum(muteDrum);
	veloFactor = velocity / 127.0;
	veloToStart = 0;
	attackValue = 0;
	decayValue = 2;
	veloToAttack = 0;
	decayMode = 0;
	veloToLevel = 100;
	auto lOscVars = oscVars.lock();
	tune = lOscVars->getTune();

	if (np != nullptr) {
		tune += np->getTune();
		veloToStart = np->getVelocityToStart();
		attackValue = np->getAttack();
		decayValue = np->getDecay();
		veloToAttack = np->getVelocityToAttack();
		decayMode = np->getDecayMode();
		veloToLevel = np->getVeloToLevel();
	}
	switch (varType) {
	case 0:
		tune += (varValue - 64) * 2;
		break;
	case 1:
		decayValue = varValue;
		decayMode = 1;
		break;
	case 2:
		attackValue = varValue;
		break;
	}

	increment = pow(2.0, ((double)(tune) / 120.0)) * (44100.0 / sampleRate);

	start = lOscVars->getStart() + (veloFactor * (veloToStart / 100.0) * lOscVars->getLastFrameIndex());
	end = lOscVars->getEnd();
	position = start;
	sampleData = lOscVars->getSampleData();
	playableSampleLength = lOscVars->isLoopEnabled() ? INT_MAX : (int)((end - start) / increment);
	attackMs = (float)((attackValue / 100.0) * MAX_ATTACK_LENGTH_MS);
	attackMs += (float)((veloToAttack / 100.0) * MAX_ATTACK_LENGTH_MS * veloFactor);
	finalDecayValue = decayValue < 2 ? 2 : decayValue;
	decayMs = (float)((finalDecayValue / 100.0) * MAX_DECAY_LENGTH_MS);
	attackLengthSamples = (int)(attackMs * (sampleRate / 1000.0));
	decayLengthSamples = (int)(decayMs * (sampleRate / 1000.0));
	if (attackLengthSamples > MAX_ATTACK_LENGTH_SAMPLES) {
		attackLengthSamples = (int)(MAX_ATTACK_LENGTH_SAMPLES);
	}

	if (decayLengthSamples > MAX_DECAY_LENGTH_SAMPLES) {
		decayLengthSamples = MAX_DECAY_LENGTH_SAMPLES;
	}

	holdLengthSamples = playableSampleLength - attackLengthSamples - decayLengthSamples;
	staticEnv->reset();
	sattack->setValue(STATIC_ATTACK_LENGTH);
	auto staticEnvHoldSamples = (int)(playableSampleLength - (((STATIC_ATTACK_LENGTH + STATIC_DECAY_LENGTH) / timeRatio) * (sampleRate / 1000.0)));
	shold->setValue(staticEnvHoldSamples);
	sdecay->setValue(STATIC_DECAY_LENGTH);
	veloToLevelFactor = (float)((veloToLevel / 100.0));
	amplitude = (float)(((veloFactor * veloToLevelFactor) + 1.0f - veloToLevelFactor));
	amplitude *= (lOscVars->getSndLevel() / 100.0);
	if (!basic) {
		ampEnv->reset();
		attack->setValue(decayMode == 1 ? (float)(0) : attackMs * timeRatio);
		hold->setValue(decayMode == 1 ? 0 : holdLengthSamples);
		decay->setValue(decayMs * timeRatio);
		filtParam = np->getFilterFrequency();
		if (varType == 3) filtParam = varValue;

		initialFilterValue = (float)(((filtParam + (veloFactor * np->getVelocityToFilterFrequency()))));
		initialFilterValue = (float)((17.0 + (initialFilterValue * 0.75)));
		filterEnv->reset();
		fattack->setValue((float)((np->getFilterAttack() * 0.002) * MAX_ATTACK_LENGTH_SAMPLES));
		fhold->setValue(0);
		fdecay->setValue((float)((np->getFilterDecay() * 0.002) * MAX_DECAY_LENGTH_SAMPLES));
		reso->setValue((float)(0.0625 + (np->getFilterResonance() / 26.0)));
		mix->setValue(0.0f);
		bandpass->setValue(false);
		svf0->update();
		svf1->update();
	}
	decayCounter = 0;
	readyToPlay = true;
}

void MpcVoice::setSampleRate(int sampleRate) {
	if (!readyToPlay) {
		return;
	}

	this->sampleRate = sampleRate;

	auto lOscVars = oscVars.lock();

	start = lOscVars->getStart() + (veloFactor * (veloToStart * 0.01) * lOscVars->getLastFrameIndex());
	end = lOscVars->getEnd();

	sampleData = lOscVars->getSampleData();

	increment = pow(2.0, ((double)(tune) / 120.0)) * (44100.0 / sampleRate);
	playableSampleLength = lOscVars->isLoopEnabled() ? INT_MAX : (int)((end - start) / increment);

	attackLengthSamples = (int)(attackMs * (sampleRate * 0.001));
	decayLengthSamples = (int)(decayMs * (sampleRate * 0.001));

	if (attackLengthSamples > MAX_ATTACK_LENGTH_SAMPLES) {
		attackLengthSamples = (int)(MAX_ATTACK_LENGTH_SAMPLES);
	}

	if (decayLengthSamples > MAX_DECAY_LENGTH_SAMPLES) {
		decayLengthSamples = MAX_DECAY_LENGTH_SAMPLES;
	}

	holdLengthSamples = playableSampleLength - attackLengthSamples - decayLengthSamples;

	staticEnv->reset();
	sattack->setValue(STATIC_ATTACK_LENGTH);
	auto staticEnvHoldSamples = (int)(playableSampleLength - (((STATIC_ATTACK_LENGTH + STATIC_DECAY_LENGTH) / timeRatio) * (sampleRate * 0.001)));
	shold->setValue(staticEnvHoldSamples);
	sdecay->setValue(STATIC_DECAY_LENGTH);
	veloToLevelFactor = (float)((veloToLevel * 0.01));
	amplitude = (float)(((veloFactor * veloToLevelFactor) + 1.0f - veloToLevelFactor));
	amplitude *= (lOscVars->getSndLevel() * 0.01);
	if (!basic) {
		ampEnv->reset();
		attack->setValue(decayMode == 1 ? (float)(0) : attackMs * timeRatio);
		hold->setValue(decayMode == 1 ? 0 : holdLengthSamples);
		decay->setValue(decayMs * timeRatio);
		filtParam = np->getFilterFrequency();
		if (varType == 3) filtParam = varValue;

		initialFilterValue = (float)(((filtParam + (veloFactor * np->getVelocityToFilterFrequency()))));
		initialFilterValue = (float)((17.0 + (initialFilterValue * 0.75)));
		filterEnv->reset();
		fattack->setValue((float)((np->getFilterAttack() * 0.002) * MAX_ATTACK_LENGTH_SAMPLES));
		fhold->setValue(0);
		fdecay->setValue((float)((np->getFilterDecay() * 0.002) * MAX_DECAY_LENGTH_SAMPLES));
		reso->setValue((float)(0.0625 + (np->getFilterResonance() / 26.0)));
		mix->setValue(0.0f);
		bandpass->setValue(false);
		svf0->update();
		svf1->update();
	}

}

std::vector<float> MpcVoice::getFrame()
{
	if (!readyToPlay || finished) return EMPTY_FRAME;

	if (frameOffset > 0) {
		frameOffset--;
		return EMPTY_FRAME;
	}
	envAmplitude = basic ? 1.0f : ampEnv->getEnvelope(false);
	staticEnvAmp = enableEnvs ? staticEnv->getEnvelope(staticDecay) : 1.0f;
	envAmplitude *= staticEnvAmp;

	float filterEnvFactor = 0;
	float filterFreq = 0;
	if (!basic) {
		filterFreq = ctoot::mpc::MpcSoundPlayerChannel::midiFreq(initialFilterValue * 1.44f) * inverseNyquist;
		filterEnvFactor = (float)(filterEnv->getEnvelope(false) * (np->getFilterEnvelopeAmount() * 0.01));
		filterFreq += ctoot::mpc::MpcSoundPlayerChannel::midiFreq(144) * inverseNyquist * filterEnvFactor;
	}

	readFrame();

	if (oscVars.lock()->isMono()) {
		tempFrame[0] *= envAmplitude * amplitude;
		if (!basic) {
			tempFrame[0] = svf0->filter(tempFrame[0], filterFreq);
		}
		tempFrame[1] = tempFrame[0];
	}
	else {
		tempFrame[0] *= envAmplitude * amplitude;
		tempFrame[1] *= envAmplitude * amplitude;
		if (!basic) {
			tempFrame[0] = svf0->filter(tempFrame[0], filterFreq);
			tempFrame[1] = svf1->filter(tempFrame[1], filterFreq);
		}
	}
	return tempFrame;
}

void MpcVoice::readFrame()
{
	if (oscVars.lock()->isLoopEnabled() && position > end - 1)
	{
		position = oscVars.lock()->getLoopTo();
	}

	if (position > end - 1 || (staticEnv != nullptr && staticEnv->isComplete()) || (ampEnv != nullptr && ampEnv->isComplete()))
	{
		tempFrame = EMPTY_FRAME;
		finished = true;
		return;
	}
	
	k = (int)(ceil(position));
	j = k - 1;
	
	if (j == -1)
		j = 0;

	frac = position - (double)(j);

	if (oscVars.lock()->isMono())
	{
		tempFrame[0] = ((*sampleData)[j] * (1.0f - frac)) + ((*sampleData)[k] * frac);
	}
	else
	{
		auto rOffset = sampleData->size() * 0.5;
		tempFrame[0] = ((*sampleData)[j] * (1.0f - frac)) + ((*sampleData)[k] * frac);
		tempFrame[1] = ((*sampleData)[j + rOffset] * (1.0f - frac)) + ((*sampleData)[k + rOffset] * frac);
	}

	position += increment;
}

int MpcVoice::getPadNumber()
{
	return padNumber;
}

void MpcVoice::open()
{
}

int MpcVoice::processAudio(ctoot::audio::core::AudioBuffer* buffer, int nFrames)
{
	if (buffer->getSampleRate() != sampleRate)
	{
		setSampleRate(buffer->getSampleRate());
	}

	if (finished)
	{
		buffer->makeSilence();
		return AUDIO_SILENCE;
	}
	
	auto left = buffer->getChannel(0);
	auto right = buffer->getChannel(1);

	for (int i = 0; i < nFrames; i++)
	{
		frame = getFrame();
	
		(*left)[i] = frame[0];
		(*right)[i] = frame[1];
		
		if (decayCounter != 0)
		{
			if (decayCounter == 1)
				startDecay();

			decayCounter--;
		}
	}

	if (finished)
	{
		padNumber = -1;
	}
	
	return AUDIO_OK;
}

bool MpcVoice::isFinished()
{
	return finished;
}

void MpcVoice::close()
{
}

void MpcVoice::finish()
{
	finished = true;
}

void MpcVoice::startDecay()
{
	staticDecay = true;
}

int MpcVoice::getVoiceOverlap()
{
	return oscVars.lock()->isLoopEnabled() ? 2 : np->getVoiceOverlap();
}

int MpcVoice::getStripNumber()
{
	return stripNumber;
}

bool MpcVoice::isDecaying()
{
	return staticDecay;
}

MpcMuteInfo* MpcVoice::getMuteInfo()
{
	return muteInfo;
}

void MpcVoice::startDecay(int offset)
{
	if (offset > 0)
		decayCounter = offset;
	else
		startDecay();
}

MpcVoice::~MpcVoice()
{
	delete muteInfo;
	delete staticEnvControls;
	delete staticEnv;

	if (!basic)
	{
		delete ampEnvControls;
		delete filterEnvControls;
		delete ampEnv;
		delete filterEnv;
		delete svfControls;
		delete svf0;
		delete svf1;
	}
}
