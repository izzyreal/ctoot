#pragma once

#include <audio/core/AudioControls.hpp>
#include <audio/dynamics/TremoloProcessVariables.hpp>

namespace ctoot {
	namespace audio {
		namespace dynamics {

			class TremoloControls
				: public ctoot::audio::core::AudioControls
				, public virtual TremoloProcessVariables
			{

			public:
				typedef ctoot::audio::core::AudioControls super;

			private:
				static ctoot::control::ControlLaw* rateLaw_;

			protected:
				static constexpr int32_t RATE_ID{ int32_t(1) };
				static constexpr int32_t DEPTH_ID{ int32_t(2) };

			private:
				ctoot::control::FloatControl* rateControl{  };
				ctoot::control::FloatControl* depthControl{  };

			protected:
				virtual ctoot::control::FloatControl* createRateControl();
				virtual ctoot::control::FloatControl* createDepthControl();

			public:
				float getDepth() override;
				float getRate() override;

				TremoloControls();
			protected:
				TremoloControls(const ::default_init_tag&);


			public:
				virtual bool isBypassed();

			protected:
				static ctoot::control::ControlLaw*& rateLaw();
			};

		}
	}
}
