#pragma once
#include <synth/synths/multi/MultiMidiSynth.hpp>
#include <synth/synths/multi/MultiSynthControls.hpp>

#include <vector>
#include <memory>

namespace ctoot::mpc
{
class MpcVoice;

class MpcMultiMidiSynth final
: public ctoot::synth::synths::multi::MultiMidiSynth
{
    
private:
    std::vector<std::shared_ptr<MpcVoice>> voices;
    std::vector<std::weak_ptr<MpcVoice>> weakVoices;
    
public:
    std::vector<std::weak_ptr<MpcVoice>> getVoices();
    
public:
    virtual void mpcTransportChannel(ctoot::midi::core::MidiMessage* msg, int chan, int varType, int varValue, int frameOffset, int startTick, int duration);
    
public:
    virtual void mpcTransport(ctoot::midi::core::MidiMessage* msg, int timestamp, int varType, int varValue, int frameOffset, int startTick, int duration);
    
public:
    virtual void mpcTransportChannel(
            ctoot::midi::core::MidiMessage* msg,
            ctoot::synth::SynthChannel* synthChannel,
            int varType,
            int varValue,
            int frameOffset,
            int startTick,
            int duration);
    std::weak_ptr<ctoot::synth::SynthChannel> mapChannel(int chan) override;
    
public:
    MpcMultiMidiSynth(std::shared_ptr<ctoot::synth::synths::multi::MultiSynthControls> controls);
    
};
}
