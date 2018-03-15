#pragma once

#include <audio/core/AudioControls.hpp>
#include <audio/delay/CabMicingProcess_Variables.hpp>
#include <audio/delay/DelayTap.hpp>
#include <control/ControlLaw.hpp>
#include <control/FloatControl.hpp>
#include <control/EnumControl.hpp>

namespace ctoot {
	namespace audio {
		namespace delay {

			class CabMicingNControl;
			class CabMicingDControl;
			class CabMicingControlsTap;

			class CabMicingControls
				: public ctoot::audio::core::AudioControls
				, public virtual CabMicingProcess_Variables
			{

			public:
				static constexpr int N_ID{ 0 };
				static constexpr int D_ID{ 1 };

			private:
				static constexpr float MILLIS_PER_INCH{ 0.075414784f };
				static constexpr float DRIVE_UNIT_SEPARATION{ 3.0f };
				static constexpr int NEAR_DISTANCE_ID{ 2 };
				static constexpr int COMB_ID{ 3 };
				std::weak_ptr<CabMicingNControl> nControl{  };
				std::weak_ptr<CabMicingDControl> dControl{  };
				std::weak_ptr<ctoot::control::FloatControl> nearControl;
				std::weak_ptr<ctoot::control::FloatControl> combControl;
				int n{ 2 };
				int d{ 12 };
				float separation{ d + DRIVE_UNIT_SEPARATION }, offset{ 3 }, near{ 6 };
				float levelPower{ 2.0f };
				float levelMin{ 0.1f };
				CabMicingControlsTap* n2Tap{  };
				CabMicingControlsTap* n3Tap{  };
				CabMicingControlsTap* n4Tap{  };
				std::vector<DelayTap*> taps{  };

			public:
				std::vector<DelayTap*> getTaps() override;
				void derive(ctoot::control::Control* c) override;

			public:
				virtual int extract(std::weak_ptr<ctoot::control::EnumControl> c);
				virtual void calculateTaps();

			private:
				float level(float in);
				std::shared_ptr<ctoot::control::FloatControl> createNearControl();
				std::shared_ptr<ctoot::control::FloatControl> createCombControl();

				

			public:
				CabMicingControls();

			public:
				virtual bool isBypassed();

			private:
				static std::weak_ptr<ctoot::control::ControlLaw> NEAR_DISTANCE_LAW();
				static std::weak_ptr<ctoot::control::ControlLaw> POWER_LAW();
			};
			REGISTER_TYPE(ctoot::audio::delay::, CabMicingControls)
		}
	}
}
