#pragma once

#include <control/spi/ControlServiceDescriptor.hpp>

namespace ctoot {
	namespace synth {
		namespace spi {

			class SynthChannelControlServiceDescriptor
				: public ctoot::control::spi::ControlServiceDescriptor
			{


			public:
				SynthChannelControlServiceDescriptor(
					const std::string& typeIdName, 
					int32_t moduleId, 
					const std::string& name,
					const std::string& description,
					const std::string& version);

			};

		}
	}
}
