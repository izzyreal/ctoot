#pragma once

#include <atomic>

#include <audio/core/AudioProcess.hpp>
#include "MpcMuteInfo.hpp"

namespace ctoot::control {
class FloatControl;
class BooleanControl;
}

namespace ctoot::synth::modules::filter {
class StateVariableFilter;
class StateVariableFilterControls;
}

namespace ctoot::mpc {
class MpcNoteParameters;
class MpcSound;
class MpcEnvelopeGenerator;
class MpcEnvelopeControls;
class MpcMuteInfo;

class MpcVoice
: public ctoot::audio::core::AudioProcess
{
    
private:
    float sampleRate = 44100.0;

    constexpr static const float STATIC_ATTACK_LENGTH = 10.92f;
    constexpr static const float STATIC_DECAY_LENGTH = 109.2f;
    static const int MAX_ATTACK_LENGTH_MS = 3000;
    static const int MAX_DECAY_LENGTH_MS = 2600;
    static const int MAX_ATTACK_LENGTH_SAMPLES = 132300;
    static const int MAX_DECAY_LENGTH_SAMPLES = 114660;
    static const int ATTACK_INDEX = 0;
    static const int HOLD_INDEX = 1;
    static const int DECAY_INDEX = 2;
    static const int RESO_INDEX = 1;
    static const int MIX_INDEX = 2;
    static const int BANDPASS_INDEX = 3;

    // Voice overlap mode when the voice was triggered
    int voiceOverlapMode;

    // Pointer to currently playing note parameters
    ctoot::mpc::MpcNoteParameters* noteParameters = nullptr;

    std::shared_ptr<ctoot::mpc::MpcSound> mpcSound;
    int startTick = -1;
    int tune = 0;
    double increment = 0;
    double position = 0;
    std::vector<float>* sampleData;
    ctoot::mpc::MpcEnvelopeGenerator* staticEnv = nullptr;
    ctoot::mpc::MpcEnvelopeGenerator* ampEnv = nullptr;
    ctoot::mpc::MpcEnvelopeGenerator* filterEnv = nullptr;
    float initialFilterValue = 0;
    bool staticDecay = 0;
    int note = -1;
    int velocity = 0;
    float amplitude = 0;
    ctoot::synth::modules::filter::StateVariableFilter* svfLeft = nullptr;
    ctoot::synth::modules::filter::StateVariableFilter* svfRight = nullptr;
    int end = 0;
    ctoot::control::FloatControl* attack = nullptr;
    ctoot::control::FloatControl* hold = nullptr;
    ctoot::control::FloatControl* decay = nullptr;
    ctoot::control::FloatControl* fattack = nullptr;
    ctoot::control::FloatControl* fhold = nullptr;
    ctoot::control::FloatControl* fdecay = nullptr;
    ctoot::control::FloatControl* shold = nullptr;
    ctoot::control::FloatControl* reso = nullptr;
    ctoot::mpc::MpcEnvelopeControls* ampEnvControls = nullptr;
    ctoot::mpc::MpcEnvelopeControls* staticEnvControls = nullptr;
    ctoot::mpc::MpcEnvelopeControls* filterEnvControls = nullptr;
    ctoot::synth::modules::filter::StateVariableFilterControls* svfControls = nullptr;
    bool finished = true;
    int stripNumber = -1;

private:
    void readFrame();
    void initializeSamplerateDependents();
    static float getInverseNyquist(int sampleRate) { return 2.f / sampleRate; }

private:
    static std::vector<float> EMPTY_FRAME;
    ctoot::mpc::MpcMuteInfo muteInfo;
    int frameOffset = 0;
    bool basic = false;
    int decayCounter = 0;
    bool enableEnvs = false;
    static const int SVF_OFFSET = 48;
    static const int AMPENV_OFFSET = 64;
    std::vector<float> tempFrame;
    int duration = -1;
    int varType = 0;
    int varValue = 0;
    int veloToStart = 0;
    int attackValue = 0;
    int decayValue = 0;
    int veloToAttack = 0;
    int decayMode = 0;
    int veloToLevel = 0;
    float attackMs = 0;
    int finalDecayValue = 0;
    float decayMs = 0;
    float veloToLevelFactor = 0;
    int filtParam = 0;
    float envAmplitude = 0;
    float staticEnvAmp = 0;
    double frac = 0;
    int k = 0;
    int j = 0;
    std::vector<float> frame;

    // The master level that is set in the Mixer Setup screen.
    // -Inf, -72, -66, -60, -54, -48, -42, -36, -30, -24, -18, -12, -6, 0, 6 or 12 dB.
    std::atomic_int8_t masterLevel{0};

public:
    void open() override;
    int processAudio(ctoot::audio::core::AudioBuffer* buffer, int nFrames) override;
    void close() override;
    
    bool isFinished();
    void init(int velocity,
              std::shared_ptr<ctoot::mpc::MpcSound> mpcSound,
              int note,
              ctoot::mpc::MpcNoteParameters* np,
              int varType,
              int varValue,
              int muteNote,
              int muteDrum,
              int frameOffset,
              bool enableEnvs,
              int startTick,
              int newDuration);
    std::vector<float>& getFrame();
    int getNote();
    ctoot::mpc::MpcNoteParameters* getNoteParameters();
    void startDecay();
    int getVoiceOverlap();
    int getStripNumber();
    int getStartTick();
    bool isDecaying();
    ctoot::mpc::MpcMuteInfo& getMuteInfo();
    void startDecay(int offset);
    void finish();

    void setMasterLevel(int8_t masterLevel);
    int8_t getMasterLevel();

public:
    MpcVoice(int stripNumber, bool basic);
    ~MpcVoice();
};

}
