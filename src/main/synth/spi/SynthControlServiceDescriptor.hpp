#pragma once
#include <control/spi/ControlServiceDescriptor.hpp>

namespace ctoot {
	namespace synth {
		namespace spi {

			class SynthControlServiceDescriptor
				: public ctoot::control::spi::ControlServiceDescriptor
			{

			public:
				SynthControlServiceDescriptor(std::string typeIdName, int32_t moduleId, std::string name, std::string description, std::string version);
			};

		}
	}
}
