#include <audio/filter/AbstractFilter.hpp>

#include <audio/filter/AbstractFilterObserver.hpp>
#include <audio/filter/FilterState.hpp>
#include <audio/filter/FilterDesign.hpp>
#include <audio/filter/FilterSpecification.hpp>

#include <Logger.hpp>

using namespace ctoot::audio::filter;
using namespace std;

AbstractFilter::AbstractFilter(FilterSpecification* spec, bool relative)
{
	this->spec = spec;
    levelOffset = relative ? 1.0f : 0.0f;
}

void AbstractFilter::open()
{
	auto des = getDesign();
	auto fspec = des->getFilterSpecification();
	auto freq = fspec->getFrequency();
	getDesign()->getFilterSpecification()->addObserver(specObserver);
}

void AbstractFilter::close()
{
   getDesign()->getFilterSpecification()->deleteObserver(specObserver);
}

FilterDesign* AbstractFilter::getDesign()
{
    return design;
}

void AbstractFilter::clear()
{
    for (auto i = int32_t(0); i < MAX_CHANNELS; i++) {
        if(states[i] != nullptr) {
            states[i]->clear();
        }
    }
}

FilterState* AbstractFilter::getState(int32_t chan)
{
	if (chan >= MAX_CHANNELS || chan < 0)
		return nullptr;

	if (doUpdate) {
		updateFilterCoefficients();
		doUpdate = false;
	}
	amplitudeAdj = design->getFilterSpecification()->getLevelFactor() - levelOffset;
	if (states[chan] == nullptr) {
		states[chan] = createState();
	}
	return states[chan];
}

void AbstractFilter::setSampleRate(int32_t rate)
{
	sampleRate = rate;
	design->design(rate);
	doUpdate = true;
}

void AbstractFilter::init()
{
	specObserver = new AbstractFilterObserver(this);
}

constexpr int32_t AbstractFilter::MAX_CHANNELS;
