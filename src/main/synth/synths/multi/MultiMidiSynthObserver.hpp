#pragma once
#include <synth/synths/multi/MultiMidiSynth.hpp>

#include <observer/Observer.hpp>

namespace ctoot::synth::synths::multi
{

class MultiMidiSynthObserver
: public moduru::observer::Observer
{
    
public:
    void update(moduru::observer::Observable* obs, nonstd::any a) override;
    
private:
    MultiMidiSynth* mms = nullptr;
    std::weak_ptr<MultiSynthControls> controls;
    
public:
    MultiMidiSynthObserver(MultiMidiSynth*, std::weak_ptr<MultiSynthControls>);
    
};
}
