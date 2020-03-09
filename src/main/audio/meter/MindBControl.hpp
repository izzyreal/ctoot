#pragma once

#include <control/EnumControl.hpp>

#include <thirdp/any.hpp>

namespace ctoot {
	namespace audio {
		namespace meter {

			class MindBControl
				: public ctoot::control::EnumControl
			{

			private:
				std::vector<nonstd::any> values{  };
				std::vector<float> floatValues{  };

			public:
				std::vector<nonstd::any> getValues() override;
				float getMindB();
				int getWidthLimit() override;
				
			public:
				MindBControl();

			};

		}
	}
}
