#include <audio/filter/AbstractFilterDesign.hpp>

#include <audio/filter/FilterSpecification.hpp>

using namespace ctoot::audio::filter;

AbstractFilterDesign::AbstractFilterDesign(FilterSpecification* spec)
{
    this->spec = spec;
}

FilterSpecification* AbstractFilterDesign::getFilterSpecification()
{
    return spec;
}
