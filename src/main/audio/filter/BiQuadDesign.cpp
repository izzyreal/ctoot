#include <audio/filter/BiQuadDesign.hpp>
#include <audio/filter/FilterSpecification.hpp>
#include <dsp/filter/BiQuadDesigner.hpp>

using namespace ctoot::audio::filter;

BiQuadDesign::BiQuadDesign(FilterSpecification* spec)
	: AbstractFilterDesign(spec)
{
}

void BiQuadDesign::design(int32_t sampleRate)
{
    a = ctoot::dsp::filter::BiQuadDesigner::design(spec->getShape(), spec->getLeveldB(), spec->getFrequency(), static_cast< float >(sampleRate), spec->getResonance());
}
