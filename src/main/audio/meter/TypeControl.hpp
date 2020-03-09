#pragma once

#include <control/EnumControl.hpp>

#include <thirdp/any.hpp>

#include <vector>

namespace ctoot {
	namespace audio {
		namespace meter {

			class TypeControl
				: public ctoot::control::EnumControl
			{

			private:
				std::vector<nonstd::any> values{  };
				std::vector<float> floatValues{  };

			public:
				std::vector<nonstd::any> getValues() override;
				virtual float getMaxdB();
				int32_t getWidthLimit() override;

				TypeControl();

			};

		}
	}
}
