#pragma once

#include <control/EnumControl.hpp>

#include <any>

namespace ctoot {
	namespace audio {
		namespace meter {

			class MindBControl
				: public ctoot::control::EnumControl
			{

			private:
				std::vector<std::any> values{  };
				std::vector<float> floatValues{  };

			public:
				std::vector<std::any> getValues() override;
				float getMindB();
				int getWidthLimit() override;
				
			public:
				MindBControl();

			};

		}
	}
}
