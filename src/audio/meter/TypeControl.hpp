#pragma once

#include <control/EnumControl.hpp>

#include <any>

#include <vector>

namespace ctoot {
	namespace audio {
		namespace meter {

			class TypeControl
				: public ctoot::control::EnumControl
			{

			private:
				std::vector<std::any> values{  };
				std::vector<float> floatValues{  };

			public:
				std::vector<std::any> getValues() override;
				virtual float getMaxdB();
				int32_t getWidthLimit() override;

				TypeControl();

			};

		}
	}
}
