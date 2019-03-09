#pragma once

#include <audio/filter/AbstractFilterDesign.hpp>

#include <vector>

namespace ctoot {
	namespace audio {
		namespace filter {

			class BiQuadDesign
				: public AbstractFilterDesign
			{

			public:
				std::vector<double> a{  };
			
			public:
				void design(int32_t sampleRate) override;

			public:
				BiQuadDesign(FilterSpecification* spec);
			};

		}
	}
}
