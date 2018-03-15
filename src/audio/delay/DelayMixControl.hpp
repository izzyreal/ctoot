#pragma once
#include <control/FloatControl.hpp>

#include <vector>

namespace ctoot {
	namespace audio {
		namespace delay {

			class DelayMixControl
				: public ctoot::control::FloatControl
			{

			public:
				typedef ctoot::control::FloatControl super;

			private:
				static std::vector<std::string> presetNames;

			public:
				std::vector<std::string> getPresetNames() override;
				void applyPreset(std::string name) override;

			public:
				DelayMixControl();

			};

		}
	}
}
