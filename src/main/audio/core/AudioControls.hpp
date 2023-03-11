#pragma once
#include <control/CompoundControl.hpp>
#include <control/BooleanControl.hpp>
#include <control/BypassControl.hpp>

namespace ctoot {
	namespace audio {
		namespace core {

			class AudioControls
				: public control::CompoundControl
			{

			public:
				AudioControls(int id, std::string name, int bypassId);
				AudioControls(int id, std::string name);

			};
		}
	}
}
