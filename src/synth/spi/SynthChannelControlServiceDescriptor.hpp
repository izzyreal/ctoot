#pragma once

#include <control/spi/ControlServiceDescriptor.hpp>

namespace ctoot {
	namespace synth {
		namespace spi {

			class SynthChannelControlServiceDescriptor
				: public ctoot::control::spi::ControlServiceDescriptor
			{


			public:
				SynthChannelControlServiceDescriptor(std::string typeIdName, int32_t moduleId, std::string name, std::string description, std::string version);

			};

		}
	}
}
