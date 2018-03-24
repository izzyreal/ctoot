#include <audio/filter/AbstractFilter.hpp>

#include <audio/filter/AbstractFilterObserver.hpp>
#include <audio/filter/FilterState.hpp>
#include <audio/filter/FilterDesign.hpp>
#include <audio/filter/FilterSpecification.hpp>

using namespace ctoot::audio::filter;
using namespace std;

AbstractFilter::AbstractFilter(FilterSpecification* spec, bool relative)
{
    init();
    levelOffset = relative ? 1.0f : 0.0f;
    //design = createDesign(spec);
    specObserver = new AbstractFilterObserver(this);
}

void AbstractFilter::open()
{
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
    if(chan >= MAX_CHANNELS || chan < 0)
        return nullptr;

    if(doUpdate) {
        updateFilterCoefficients();
        doUpdate = false;
    }
    amplitudeAdj = design->getFilterSpecification()->getLevelFactor() - levelOffset;
    if(states[chan] == nullptr) {
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
	design = nullptr;
	specObserver = nullptr;
	doUpdate = true;
	states = vector<FilterState*>(MAX_CHANNELS);
	amplitudeAdj = 0.0f;
	sampleRate = -int32_t(1);
}

constexpr int32_t AbstractFilter::MAX_CHANNELS;
