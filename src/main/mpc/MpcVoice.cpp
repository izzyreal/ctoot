#include <mpc/MpcVoice.hpp>

#include <mpc/MpcNoteParameters.hpp>
#include <mpc/MpcSound.hpp>

#include <mpc/MpcEnvelopeControls.hpp>
#include <mpc/MpcEnvelopeGenerator.hpp>
#include <mpc/MpcSoundPlayerChannel.hpp>

#include <audio/core/AudioBuffer.hpp>
#include <control/BooleanControl.hpp>
#include <control/FloatControl.hpp>
#include <synth/modules/filter/StateVariableFilter.hpp>
#include <synth/modules/filter/StateVariableFilterControls.hpp>

#include <cmath>

#ifdef __linux__
#include <climits>
#endif

using namespace ctoot::mpc;

std::vector<float> MpcVoice::EMPTY_FRAME = {0.f, 0.f};

MpcVoice::MpcVoice(int _stripNumber, bool _basic)
        : stripNumber(_stripNumber), basic(_basic), frame(EMPTY_FRAME) {
    tempFrame = EMPTY_FRAME;
    staticEnvControls = new ctoot::mpc::MpcEnvelopeControls(0, "StaticAmpEnv", AMPENV_OFFSET);
    staticEnv = new ctoot::mpc::MpcEnvelopeGenerator(staticEnvControls);
    shold = std::dynamic_pointer_cast<ctoot::control::FloatControl>(
            staticEnvControls->getControls()[HOLD_INDEX].lock()).get();

    auto sattack = std::dynamic_pointer_cast<ctoot::control::FloatControl>(
            staticEnvControls->getControls()[ATTACK_INDEX].lock()).get();


    auto sdecay = std::dynamic_pointer_cast<ctoot::control::FloatControl>(
            staticEnvControls->getControls()[DECAY_INDEX].lock()).get();

    sattack->setValue(STATIC_ATTACK_LENGTH);
    sdecay->setValue(STATIC_DECAY_LENGTH);

    if (!basic) {
        ampEnvControls = new ctoot::mpc::MpcEnvelopeControls(0, "AmpEnv", AMPENV_OFFSET);
        filterEnvControls = new ctoot::mpc::MpcEnvelopeControls(0, "StaticAmpEnv", AMPENV_OFFSET);
        ampEnv = new ctoot::mpc::MpcEnvelopeGenerator(ampEnvControls);
        filterEnv = new ctoot::mpc::MpcEnvelopeGenerator(filterEnvControls);
        svfControls = new ctoot::synth::modules::filter::StateVariableFilterControls(0, "Filter", SVF_OFFSET);
        svfControls->createControls();
        svfLeft = new ctoot::synth::modules::filter::StateVariableFilter(svfControls);
        svfRight = new ctoot::synth::modules::filter::StateVariableFilter(svfControls);
        fattack = std::dynamic_pointer_cast<ctoot::control::FloatControl>(
                filterEnvControls->getControls()[ATTACK_INDEX].lock()).get();
        fhold = std::dynamic_pointer_cast<ctoot::control::FloatControl>(
                filterEnvControls->getControls()[HOLD_INDEX].lock()).get();
        fdecay = std::dynamic_pointer_cast<ctoot::control::FloatControl>(
                filterEnvControls->getControls()[DECAY_INDEX].lock()).get();
        attack = std::dynamic_pointer_cast<ctoot::control::FloatControl>(
                ampEnvControls->getControls()[ATTACK_INDEX].lock()).get();
        hold = std::dynamic_pointer_cast<ctoot::control::FloatControl>(
                ampEnvControls->getControls()[HOLD_INDEX].lock()).get();
        decay = std::dynamic_pointer_cast<ctoot::control::FloatControl>(
                ampEnvControls->getControls()[DECAY_INDEX].lock()).get();
        reso = std::dynamic_pointer_cast<ctoot::control::FloatControl>(svfControls->getControls()[RESO_INDEX].lock()).get();

        auto mix = std::dynamic_pointer_cast<ctoot::control::FloatControl>(
                svfControls->getControls()[MIX_INDEX].lock()).get();
        mix->setValue(0.0f);

        auto bandpass = std::dynamic_pointer_cast<ctoot::control::BooleanControl>(
                svfControls->getControls()[BANDPASS_INDEX].lock()).get();

        bandpass->setValue(false);
    }
}

void MpcVoice::init(
        int newVelocity,
        std::shared_ptr<ctoot::mpc::MpcSound> newMpcSound,
        int newNote,
        ctoot::mpc::MpcNoteParameters *np,
        int newVarType,
        int newVarValue,
        int muteNote,
        int muteDrum,
        int newFrameOffset,
        bool newEnableEnvs,
        int newStartTick,
        int newDuration
) {
    finished = false;

    duration = newDuration;

    noteParameters = np;
    startTick = newStartTick;

    enableEnvs = newEnableEnvs;
    frameOffset = newFrameOffset;
    note = newNote;
    velocity = newVelocity;
    mpcSound = newMpcSound;
    varType = newVarType;
    varValue = newVarValue;

    staticDecay = false;
    muteInfo.setNote(muteNote);
    muteInfo.setDrum(muteDrum);
    veloToStart = 0;
    attackValue = 0;
    decayValue = 2;
    veloToAttack = 0;
    decayMode = 0;
    veloToLevel = 100;

    auto lMpcSound = mpcSound;

    tune = lMpcSound->getTune();

    if (np != nullptr) {
        tune += np->getTune();
        veloToStart = np->getVelocityToStart();
        attackValue = np->getAttack();
        decayValue = np->getDecay();
        veloToAttack = np->getVelocityToAttack();
        decayMode = np->getDecayMode();
        veloToLevel = np->getVeloToLevel();
        voiceOverlapMode = np->getVoiceOverlap();
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

    const auto veloFactor = velocity / 127.f;
    const auto inverseVeloFactor = 1.f - veloFactor;

    end = lMpcSound->getEnd();

    position = lMpcSound->getStart() + (inverseVeloFactor * (veloToStart / 100.0) * lMpcSound->getLastFrameIndex());
    sampleData = lMpcSound->getSampleData();
    attackMs = (float) ((attackValue / 100.0) * MAX_ATTACK_LENGTH_MS);
    attackMs += (float) ((veloToAttack / 100.0) * MAX_ATTACK_LENGTH_MS * veloFactor);
    finalDecayValue = decayValue < 2 ? 2 : decayValue;
    decayMs = (float) ((finalDecayValue / 100.0) * MAX_DECAY_LENGTH_MS);
    staticEnv->reset();
    veloToLevelFactor = (float) (veloToLevel * 0.01);
    amplitude = (float) ((veloFactor * veloToLevelFactor) + 1.0f - veloToLevelFactor);
    amplitude *= (lMpcSound->getSndLevel() * 0.01);

    if (!basic) {
        ampEnv->reset();
        filtParam = np->getFilterFrequency();

        if (varType == 3) {
            filtParam = varValue;
        }

        initialFilterValue = (float) (filtParam + (veloFactor * np->getVelocityToFilterFrequency()));
        initialFilterValue = (float) (17.0 + (initialFilterValue * 0.75));
        filterEnv->reset();
        fattack->setValue((float) (np->getFilterAttack() * 0.002) * MAX_ATTACK_LENGTH_SAMPLES);
        fhold->setValue(0);
        fdecay->setValue((float) (np->getFilterDecay() * 0.002) * MAX_DECAY_LENGTH_SAMPLES);
        reso->setValue((float) (0.0625 + (np->getFilterResonance() / 26.0)));
        svfLeft->update();
        svfRight->update();
    }

    decayCounter = 0;

    initializeSamplerateDependents();
}

void MpcVoice::initializeSamplerateDependents()
{
    staticEnvControls->setSampleRate(sampleRate);

    if (!basic) {
        ampEnvControls->setSampleRate(sampleRate);
        filterEnvControls->setSampleRate(sampleRate);
        svfControls->setSampleRate(sampleRate);
    }

    auto lMpcSound = mpcSound;

    increment = pow(2.0, ((double) (tune) / 120.0)) * (44100.0 / sampleRate);

    const auto veloFactor = 1.f - (velocity / 127.f);
    auto start = lMpcSound->getStart() + (veloFactor * (veloToStart / 100.0) * lMpcSound->getLastFrameIndex());

    auto playableSampleLength = lMpcSound->isLoopEnabled() ? INT_MAX : (int) ((end - start) / increment);

    auto attackLengthSamples = (int) (attackMs * sampleRate * 0.001);
    auto decayLengthSamples = (int) (decayMs * sampleRate * 0.001);

    if (attackLengthSamples > MAX_ATTACK_LENGTH_SAMPLES) {
        attackLengthSamples = (int) (MAX_ATTACK_LENGTH_SAMPLES);
    }

    if (decayLengthSamples > MAX_DECAY_LENGTH_SAMPLES) {
        decayLengthSamples = MAX_DECAY_LENGTH_SAMPLES;
    }

    auto timeRatio = 5.46f;
    auto staticEnvHoldSamples = (int) (playableSampleLength - ((STATIC_ATTACK_LENGTH + STATIC_DECAY_LENGTH) / timeRatio) * (sampleRate) * 0.001);

    if (duration != -1 && duration < playableSampleLength)
    {
        staticEnvHoldSamples = (int) (duration - ((STATIC_ATTACK_LENGTH + STATIC_DECAY_LENGTH) / timeRatio) * (sampleRate) * 0.001);
    }

    shold->setValue(staticEnvHoldSamples);

    if (!basic) {
        auto holdLengthSamples = playableSampleLength - attackLengthSamples - decayLengthSamples;
        attack->setValue(decayMode == 1 ? (float) (0) : attackMs * timeRatio);
        hold->setValue(decayMode == 1 ? 0 : holdLengthSamples);
        decay->setValue(decayMs * timeRatio);
    }
}

std::vector<float>& MpcVoice::getFrame() {
    if (finished)
        return EMPTY_FRAME;

    if (frameOffset > 0) {
        frameOffset--;
        return EMPTY_FRAME;
    }

    envAmplitude = basic ? 1.0f : ampEnv->getEnvelope(false);
    staticEnvAmp = enableEnvs ? staticEnv->getEnvelope(staticDecay) : 1.0f;
    envAmplitude *= staticEnvAmp;

    float filterFreq = 0;

    if (!basic) {
        auto invNyquist = getInverseNyquist(sampleRate);
        filterFreq = ctoot::mpc::MpcSoundPlayerChannel::midiFreq(initialFilterValue * 1.44f) * invNyquist;
        auto filterEnvFactor = (float) (filterEnv->getEnvelope(false) * (noteParameters->getFilterEnvelopeAmount() * 0.01));
        filterFreq += ctoot::mpc::MpcSoundPlayerChannel::midiFreq(144) * invNyquist * filterEnvFactor;
    }

    readFrame();

    if (mpcSound->isMono()) {
        tempFrame[0] *= envAmplitude * amplitude;

        if (!basic)
            tempFrame[0] = svfLeft->filter(tempFrame[0], filterFreq);

        tempFrame[1] = tempFrame[0];
    } else {
        tempFrame[0] *= envAmplitude * amplitude;
        tempFrame[1] *= envAmplitude * amplitude;

        if (!basic) {
            tempFrame[0] = svfLeft->filter(tempFrame[0], filterFreq);
            tempFrame[1] = svfRight->filter(tempFrame[1], filterFreq);
        }
    }

    return tempFrame;
}

void MpcVoice::readFrame() {
    if (mpcSound->isLoopEnabled() && position > end - 1)
        position = mpcSound->getLoopTo();

    if ( ( (position >= (end - 1)) && !mpcSound->isLoopEnabled() ) || (staticEnv != nullptr && staticEnv->isComplete()) ||
        (ampEnv != nullptr && ampEnv->isComplete())) {
        tempFrame = EMPTY_FRAME;
        finished = true;
        return;
    }

    k = (int) (ceil(position));
    j = k - 1;

    if (j == -1)
        j = 0;

    frac = position - (double) (j);

    if (mpcSound->isMono()) {
        tempFrame[0] = ((*sampleData)[j] * (1.0f - frac)) + ((*sampleData)[k] * frac);
    } else {
        auto rOffset = sampleData->size() * 0.5;
        tempFrame[0] = ((*sampleData)[j] * (1.0f - frac)) + ((*sampleData)[k] * frac);
        tempFrame[1] = ((*sampleData)[j + rOffset] * (1.0f - frac)) + ((*sampleData)[k + rOffset] * frac);
    }

    position += increment;
}

void MpcVoice::open() {
}

int MpcVoice::processAudio(ctoot::audio::core::AudioBuffer *buffer, int nFrames) {
    if (finished) {
        buffer->makeSilence();
        return AUDIO_SILENCE;
    }

    if (buffer->getSampleRate() != sampleRate) {
        sampleRate = buffer->getSampleRate();
        initializeSamplerateDependents();
    }

    auto& left = buffer->getChannel(0);
    auto& right = buffer->getChannel(1);

    auto masterLevelToUse = masterLevel.load();

    auto masterLevelFactor = masterLevelToUse > -128 ? std::pow (10.f, static_cast<float>(masterLevelToUse) * 0.04f)
                                                        : 0;

    for (int i = 0; i < nFrames; i++) {
        frame = getFrame();

        left[i] = frame[0] * masterLevelFactor;
        right[i] = frame[1] * masterLevelFactor;

        if (decayCounter != 0) {
            if (decayCounter == 1)
            {
                startDecay();
            }

            decayCounter--;
        }
    }

    if (finished) {
        note = -1;
        mpcSound = {};
    }

    return AUDIO_OK;
}

bool MpcVoice::isFinished() {
    return finished;
}

void MpcVoice::close() {
}

void MpcVoice::finish() {
    finished = true;
}

void MpcVoice::startDecay() {
    staticDecay = true;
}

int MpcVoice::getVoiceOverlap() {
    return mpcSound->isLoopEnabled() ? 2 : voiceOverlapMode;
}

int MpcVoice::getStripNumber() {
    return stripNumber;
}

int MpcVoice::getStartTick()
{
    return startTick;
}

bool MpcVoice::isDecaying() {
    return staticDecay;
}

MpcMuteInfo& MpcVoice::getMuteInfo() {
    return muteInfo;
}

void MpcVoice::startDecay(int offset) {
    if (offset > 0)
        decayCounter = offset;
    else
        startDecay();
}

int MpcVoice::getNote() {
    return note;
}

ctoot::mpc::MpcNoteParameters *MpcVoice::getNoteParameters() {
    return noteParameters;
}

void MpcVoice::setMasterLevel(int8_t masterLevelToUse)
{
    masterLevel.store(masterLevelToUse);
}

int8_t MpcVoice::getMasterLevel()
{
    return masterLevel.load();
}

MpcVoice::~MpcVoice() {
    delete staticEnvControls;
    delete staticEnv;

    if (!basic) {
        delete ampEnvControls;
        delete filterEnvControls;
        delete ampEnv;
        delete filterEnv;
        delete svfControls;
        delete svfLeft;
        delete svfRight;
    }
}
