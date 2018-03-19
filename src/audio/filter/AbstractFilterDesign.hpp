#pragma once

#include <audio/filter/FilterDesign.hpp>

namespace ctoot {
	namespace audio {
		namespace filter {

			class FilterSpecification;

			class AbstractFilterDesign
				: public virtual FilterDesign
			{

			protected:
				FilterSpecification* spec{  };

			public:
				FilterSpecification* getFilterSpecification() override;

			public:
				AbstractFilterDesign(FilterSpecification* spec);
			};

		}
	}
}
