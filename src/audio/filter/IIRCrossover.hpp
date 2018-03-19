#pragma once
#include <audio/filter/Crossover.hpp>

#include <vector>

namespace ctoot {
	namespace audio {
		namespace filter {
			class Filter;
			class FilterSpecification;
			class IIRCrossover
				: public virtual Crossover
			{

			private:
				Filter* hpf{  };
				Filter* lpf{  };

			public:
				void setSampleRate(int32_t rate) override;
				void filter(std::vector<float>* source, std::vector<float>* lo, std::vector<float>* hi, int32_t nsamples, int32_t chan) override;
				void clear() override;

			public:
				IIRCrossover(FilterSpecification* low, FilterSpecification* high);
			};
		}
	}
}
