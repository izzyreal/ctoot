#pragma once

#include <dsp/filter/FilterShape.hpp>

#include <observer/Observer.hpp>

namespace ctoot {

	namespace audio {
		namespace filter {

			class FilterSpecification
			{
			public:
				virtual ctoot::dsp::filter::FilterShape getShape() = 0;
				virtual int32_t getFrequency() = 0;
				virtual float getResonance() = 0;
				virtual float getLeveldB() = 0;
				virtual float getLevelFactor() = 0;
				virtual bool is4thOrder() = 0;
				virtual void addObserver(moduru::observer::Observer* observer) = 0;
				virtual void deleteObserver(moduru::observer::Observer* observer) = 0;
			};

		}
	}
}
