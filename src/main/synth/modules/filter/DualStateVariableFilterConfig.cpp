#include <synth/modules/filter/DualStateVariableFilterConfig.hpp>

#include <synth/modules/filter/FilterType.hpp>

using namespace ctoot::synth::modules::filter;

DualStateVariableFilterConfig::DualStateVariableFilterConfig(std::string name, int32_t t1, int32_t t2, int32_t ratio)
{
    this->name = name;
    /* assert(t1 >= 0 && t1 <= FilterType::PEAK) */ ;
    /* assert(t2 >= 0 && t2 <= FilterType::PEAK) */ ;
    /* assert(ratio > 0 && ratio < 10) */ ;
    type1 = t1;
    type2 = t2;
    f2ratio = ratio;
}

std::string ctoot::synth::modules::filter::DualStateVariableFilterConfig::toString()
{
    return name;
}
