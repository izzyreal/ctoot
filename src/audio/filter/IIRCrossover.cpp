#include <audio/filter/IIRCrossover.hpp>

#include <audio/filter/BiQuadFilter.hpp>
#include <audio/filter/Filter.hpp>

#include <audio/filter/FilterSpecification.hpp>

using namespace ctoot::audio::filter;

IIRCrossover::IIRCrossover(FilterSpecification* low, FilterSpecification* high)
{
    lpf = new BiQuadFilter(low, true);
    hpf = new BiQuadFilter(high, true);
    lpf->open();
    hpf->open();
}

void IIRCrossover::setSampleRate(int32_t rate)
{
    lpf->setSampleRate(rate);
    hpf->setSampleRate(rate);
}

void IIRCrossover::filter(std::vector<float>* source, std::vector<float>* lo, std::vector<float>* hi, int32_t nsamples, int32_t chan)
{
	if (hi != nullptr)
		hpf->filter(source, hi, nsamples, chan, false);
	if (lo != nullptr)
		lpf->filter(source, lo, nsamples, chan, false);
}

void IIRCrossover::clear()
{
    lpf->clear();
    hpf->clear();
}

IIRCrossover::~IIRCrossover() {
	if (lpf != nullptr) delete lpf;
	if (hpf != nullptr) delete hpf;
}
