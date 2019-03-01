#pragma once

#include <control/EnumControl.hpp>

#include <any>

namespace ctoot {
	namespace audio {
		namespace delay {
			
			class TempoDelayControls;

			class DelayFactorControl
				: public ctoot::control::EnumControl
			{

			public:
				typedef ctoot::control::EnumControl super;

			public:
				std::vector<std::any> getValues() override;
				void setValue(std::any value) override;
				bool hasLabel() override;

			public:
				DelayFactorControl(TempoDelayControls *TempoDelayControls_this);

			public:				
				TempoDelayControls *TempoDelayControls_this;
			};

		}
	}
}
