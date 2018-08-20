#pragma once

#include <control/EnumControl.hpp>

#include <boost/any.hpp>

#include <vector>

namespace ctoot {
	namespace audio {
		namespace meter {

			class TypeControl
				: public ctoot::control::EnumControl
			{

			private:
				std::vector<boost::any> values{  };
				std::vector<float> floatValues{  };

			public:
				std::vector<boost::any> getValues() override;
				virtual float getMaxdB();
				int32_t getWidthLimit() override;

				TypeControl();

			};

		}
	}
}
