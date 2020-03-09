#pragma once

#include <control/EnumControl.hpp>

#include <vector>
#include <string>
#include <thirdp/any.hpp>

namespace ctoot {
	namespace audio {
		namespace dynamics {
			namespace izcompressor {

				class ChannelControl
					: public ctoot::control::EnumControl
				{

				public:
					ChannelControl(int32_t id, std::string name);
					~ChannelControl();

				public:
					std::vector<nonstd::any> getValues() override;

				};
				
			}
		}
	}
}
