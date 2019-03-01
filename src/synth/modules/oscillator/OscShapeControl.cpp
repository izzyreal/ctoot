#include <synth/modules/oscillator/OscShapeControl.hpp>

#include <synth/modules/oscillator/LFOControls.hpp>

using namespace ctoot::synth::modules::oscillator;

ShapeControl::ShapeControl(int32_t id, std::string name, std::any value)
	: ctoot::control::EnumControl(id, name, value)
{
}

std::vector<std::any> ShapeControl::getValues()
{
	std::vector<std::any> res{ std::string("Sine"), std::string("Triangle") };
    return res;
}
