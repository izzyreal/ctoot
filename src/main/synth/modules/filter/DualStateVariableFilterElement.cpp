#include <synth/modules/filter/DualStateVariableFilterElement.hpp>

#include <synth/modules/filter/DualStateVariableFilterConfig.hpp>
#include <synth/modules/filter/FilterType.hpp>

using namespace ctoot::synth::modules::filter;

DualStateVariableFilterElement::DualStateVariableFilterElement()
{
}

float DualStateVariableFilterElement::filter(float in, DualStateVariableFilterConfig* config)
{
	auto i1 = (prev + in) * 0.5f;
	prev = in;
	notch1 = i1 - config->damp1 * band1;
	low1 = low1 + config->freq1 * band1;
	high1 = notch1 - low1;
	band1 = config->freq1 * high1 + band1;
	if (config->type2 != FilterType::OFF) {
		switch (config->type1) {
		case FilterType::LOW:
			i1 = low1;
			break;
		case FilterType::HIGH:
			i1 = high1;
			break;
		case FilterType::NOTCH:
			i1 = notch1;
			break;
		case FilterType::BAND:
			i1 = band1;
			break;
		case FilterType::PEAK:
			i1 += band1;
			break;
		}

		notch = i1 - config->damp2 * band;
		low = low + config->freq2 * band;
		high = notch - low;
		band = config->freq2 * high + band;
	}
	notch1 = in - config->damp1 * band1;
	low1 = low1 + config->freq1 * band1;
	high1 = notch1 - low1;
	band1 = config->freq1 * high1 + band1;
	if (config->type2 == FilterType::OFF) {
		switch (config->type1) {
		case FilterType::LOW:
			return low1;
		case FilterType::HIGH:
			return high1;
		case FilterType::NOTCH:
			return notch1;
		case FilterType::BAND:
			return band1;
		case FilterType::PEAK:
			return in + band1;
		}

	}
	switch (config->type1) {
	case FilterType::LOW:
		i1 = low1;
		break;
	case FilterType::HIGH:
		i1 = high1;
		break;
	case FilterType::NOTCH:
		i1 = notch1;
		break;
	case FilterType::BAND:
		i1 = band1;
		break;
	case FilterType::PEAK:
		i1 = in + band1;
		break;
	}

	notch = i1 - config->damp2 * band;
	low = low + config->freq2 * band;
	high = notch - low;
	band = config->freq2 * high + band;
	{
		float tmp;
		switch (config->type2) {
		case FilterType::LOW:
			return low;
		case FilterType::HIGH:
			return high;
		case FilterType::NOTCH:
			return notch;
		case FilterType::BAND:
			return band;
		case FilterType::PEAK:
			tmp = i1 + band;
			return config->type1 == FilterType::PEAK ? tmp * 0.5f : tmp;
		}
	}

	return in;
}
