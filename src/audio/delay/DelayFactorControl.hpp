#pragma once

#include <control/EnumControl.hpp>

#include <boost/any.hpp>

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
				std::vector<boost::any> getValues() override;
				void setValue(boost::any value) override;
				bool hasLabel() override;

			public:
				DelayFactorControl(TempoDelayControls *TempoDelayControls_this);

			public:				
				TempoDelayControls *TempoDelayControls_this;
			};

		}
	}
}
