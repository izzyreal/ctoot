#pragma once

#include <audio/core/AudioControls.hpp>
#include <audio/dynamics/TremoloProcessVariables.hpp>

#include <memory>

namespace ctoot {

	namespace control {
		class ControlLaw;
		class FloatControl;
	}

	namespace audio {
		namespace dynamics {

			class TremoloControls
				: public ctoot::audio::core::AudioControls
				, public virtual TremoloProcessVariables
			{

			private:
				static std::weak_ptr<ctoot::control::ControlLaw> rateLaw();

			protected:
				static constexpr int32_t RATE_ID{ int32_t(1) };
				static constexpr int32_t DEPTH_ID{ int32_t(2) };

			private:
				std::weak_ptr<ctoot::control::FloatControl> rateControl{  };
				std::weak_ptr<ctoot::control::FloatControl> depthControl{  };

			protected:
				virtual std::shared_ptr<ctoot::control::FloatControl> createRateControl();
				virtual std::shared_ptr<ctoot::control::FloatControl> createDepthControl();

			public:
				float getDepth() override;
				float getRate() override;

				TremoloControls();

			public:
				virtual bool isBypassed() override;

			};
			REGISTER_TYPE(ctoot::audio::dynamics::, TremoloControls)
		}
	}
}
