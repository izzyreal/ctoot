#pragma once

#include <control/EnumControl.hpp>

#include <boost/any.hpp>

namespace ctoot {
	namespace audio {
		namespace meter {

			class MindBControl
				: public ctoot::control::EnumControl
			{

			private:
				std::vector<boost::any> values{  };
				std::vector<float> floatValues{  };

			public:
				std::vector<boost::any> getValues() override;
				float getMindB();
				int getWidthLimit() override;
				
			public:
				MindBControl();

			};

		}
	}
}