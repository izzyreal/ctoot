#include <synth/modules/oscillator/ShapeControl.hpp>

#include <synth/modules/oscillator/LFOControls.hpp>

using namespace ctoot::synth::modules::oscillator;

java::util::List* ShapeControl::getValues()
{
    return shapeNames;
}
