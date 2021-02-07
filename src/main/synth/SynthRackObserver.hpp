#pragma once
#include <observer/Observer.hpp>

#include <memory>

namespace ctoot::synth {
class SynthRack;
class SynthRackControls;
}

namespace ctoot::synth {
class SynthRackObserver
: public moduru::observer::Observer
{
public:
    SynthRackObserver(SynthRack*, std::weak_ptr<SynthRackControls>);
    SynthRack* sr = nullptr;
    std::weak_ptr<SynthRackControls> controls;
    void update(moduru::observer::Observable*, nonstd::any) override;
};
}
