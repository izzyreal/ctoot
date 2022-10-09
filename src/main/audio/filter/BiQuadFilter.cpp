#include <audio/filter/BiQuadFilter.hpp>

#include <audio/core/FloatDenormals.hpp>
#include <audio/filter/BiQuadDesign.hpp>
#include <audio/filter/BiQuadState.hpp>
#include <audio/filter/FilterState.hpp>
#include <audio/filter/FilterDesign.hpp>

#include <audio/filter/AbstractFilterObserver.hpp>

using namespace ctoot::audio::filter;

BiQuadFilter::BiQuadFilter(FilterSpecification* spec, bool relative)
	: AbstractFilter(spec, relative)
{
	design = createDesign(spec);
	specObserver = new AbstractFilterObserver(this);
}

/*
void BiQuadFilter::init() {
	design = createDesign(spec);
	AbstractFilter::init();
}
*/

void BiQuadFilter::filter(std::vector<float>& buffer, std::vector<float>& mixBuffer, int32_t length, int32_t chan, bool doMix)
{
	auto s = dynamic_cast<BiQuadState*>(getState(chan));
    float sample;
    float y;
    for (auto index = int32_t(0); index < length; index++) {
        sample = buffer[index];
        y = static_cast< float >(a0 * sample + a1 * s->x1 + a2 * s->x2 - a3 * s->y1 - a4 * s->y2);
        y = ctoot::audio::core::FloatDenormals::zeroDenorm(y);
        s->x2 = s->x1;
        s->x1 = sample;
        s->y2 = s->y1;
        s->y1 = y;
        if(!doMix) {
            mixBuffer[index] = y;
        } else {
            mixBuffer[index] += (amplitudeAdj * y);
        }
    }
}

void BiQuadFilter::updateFilterCoefficients()
{
    auto d = dynamic_cast<BiQuadDesign*>(getDesign());
    a0 = d->a[0];
    a1 = d->a[1];
    a2 = d->a[2];
    a3 = d->a[3];
    a4 = d->a[4];
}

FilterDesign* BiQuadFilter::createDesign(FilterSpecification* spec)
{
    return new BiQuadDesign(spec);
}

FilterState* BiQuadFilter::createState()
{
    return new BiQuadState();
}
