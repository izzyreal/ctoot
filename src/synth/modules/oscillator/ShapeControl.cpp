#include <synth/modules/oscillator/ShapeControl.hpp>

#include <synth/modules/oscillator/LFOControls.hpp>

using namespace ctoot::synth::modules::oscillator;

ShapeControl::ShapeControl(int32_t id, std::string name, boost::any value)
	: ctoot::control::EnumControl(id, name, value)
{
}

std::vector<boost::any> ShapeControl::getValues()
{
	std::vector<boost::any> res{ std::string("Sine"), std::string("Triangle") };
    return res;
}