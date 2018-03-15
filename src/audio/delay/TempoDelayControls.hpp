#pragma once

#include <audio/delay/AbstractDelayControls.hpp>
#include <audio/delay/TempoDelayProcessVariables.hpp>

#include <control/LinearLaw.hpp>
#include <control/LogLaw.hpp>

#include <memory>

namespace ctoot {
	namespace audio {
		namespace delay {

			class NamedFactor;

			class TempoDelayControls
				: public AbstractDelayControls
				, public virtual TempoDelayProcessVariables
			{

			public:
				typedef AbstractDelayControls super;
				float delayFactor{};

			private:
				static std::weak_ptr<ctoot::control::LinearLaw> DUCKING_LAW();
				static std::weak_ptr<ctoot::control::LogLaw> CUTOFF_LAW();
				static constexpr int DUCKING_ID{ int(0) };
				static constexpr int LOWPASS_ID{ int(1) };
				std::weak_ptr<ctoot::control::FloatControl> duckingControl;
				std::weak_ptr<ctoot::control::FloatControl> lowpassControl;
				float ducking{}, lowpassCoeff{};

			public:
				void derive(ctoot::control::Control* c) override;
				virtual std::shared_ptr<ctoot::control::FloatControl> createDuckingControl();
				virtual std::shared_ptr<ctoot::control::FloatControl> createLowpassControl();

			public:
				float getDucking() override;
				float getLowpassCoefficient() override;
				float getDelayFactor() override;
				float getMaxDelayMilliseconds() override;

			public:
				TempoDelayControls();

			public:
				virtual bool isBypassed();
				virtual float getFeedback();
				virtual float getMix();

			public:
				static std::vector<NamedFactor*> factors();
				static NamedFactor* defaultFactor();
			};
			REGISTER_TYPE(ctoot::audio::delay::, TempoDelayControls)
		}
	}
}
