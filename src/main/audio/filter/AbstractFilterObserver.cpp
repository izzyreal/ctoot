#include <audio/filter/AbstractFilterObserver.hpp>

#include <audio/filter/AbstractFilter.hpp>
#include <audio/filter/FilterDesign.hpp>

using namespace ctoot::audio::filter;

AbstractFilterObserver::AbstractFilterObserver(AbstractFilter* af) {
	this->af = af;
}

void AbstractFilterObserver::update(moduru::observer::Observable* obs, std::any arg)
{
    if (af->sampleRate < 1)
        return;

    af->design->design(af->sampleRate);
    af->doUpdate = true;
}
