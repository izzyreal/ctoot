#include <synth/modules/filter/DualStateVariableFilterControlsTypeControl.hpp>

#include <synth/modules/filter/DualStateVariableFilterConfig.hpp>
#include <synth/modules/filter/DualStateVariableFilterControls.hpp>
#include <synth/modules/filter/FilterType.hpp>

using namespace ctoot::synth::modules::filter;

DualStateVariableFilterControlsTypeControl::DualStateVariableFilterControlsTypeControl(int32_t id, std::string name)
	: ctoot::control::EnumControl(id, name, nullptr)
{
	createValues();
	setValue(getValues()[0]);
}

void DualStateVariableFilterControlsTypeControl::createValues()
{
    values.push_back(new DualStateVariableFilterConfig("L2", FilterType::LOW, FilterType::OFF, 1));
    values.push_back(new DualStateVariableFilterConfig("L4", FilterType::LOW, FilterType::LOW, 1));
    values.push_back(new DualStateVariableFilterConfig("H2", FilterType::HIGH, FilterType::OFF, 1));
    values.push_back(new DualStateVariableFilterConfig("H4", FilterType::HIGH, FilterType::HIGH, 1));
    values.push_back(new DualStateVariableFilterConfig("N2", FilterType::NOTCH, FilterType::OFF, 1));
    values.push_back(new DualStateVariableFilterConfig("N4", FilterType::NOTCH, FilterType::NOTCH, 1));
    values.push_back(new DualStateVariableFilterConfig("B2", FilterType::BAND, FilterType::OFF, 1));
    values.push_back(new DualStateVariableFilterConfig("B4", FilterType::BAND, FilterType::BAND, 1));
    values.push_back(new DualStateVariableFilterConfig("P2", FilterType::PEAK, FilterType::OFF, 1));
    values.push_back(new DualStateVariableFilterConfig("P4", FilterType::PEAK, FilterType::PEAK, 1));
    values.push_back(new DualStateVariableFilterConfig("H2N2", FilterType::HIGH, FilterType::NOTCH, 1));
    values.push_back(new DualStateVariableFilterConfig("N2L2", FilterType::NOTCH, FilterType::LOW, 1));
    values.push_back(new DualStateVariableFilterConfig("H2N2T", FilterType::HIGH, FilterType::NOTCH, 2));
    values.push_back(new DualStateVariableFilterConfig("N2L2T", FilterType::NOTCH, FilterType::LOW, 2));
    values.push_back(new DualStateVariableFilterConfig("N2N2T", FilterType::NOTCH, FilterType::NOTCH, 2));
    values.push_back(new DualStateVariableFilterConfig("N2P2T", FilterType::NOTCH, FilterType::PEAK, 2));
    values.push_back(new DualStateVariableFilterConfig("P2N2T", FilterType::PEAK, FilterType::NOTCH, 2));
}

std::vector<std::any> ctoot::synth::modules::filter::DualStateVariableFilterControlsTypeControl::getValues()
{
    return values;
}

int32_t ctoot::synth::modules::filter::DualStateVariableFilterControlsTypeControl::getWidthLimit()
{
    return 55;
}
