#pragma once
#include <audio/dynamics/DynamicsControls.hpp>

#include <memory>
#include <string>

namespace ctoot {

	namespace control {
		class ControlLaw;
	}

	namespace audio {
		namespace dynamics {

			class BusCompressorControls
				: public DynamicsControls
			{

			private:
				static std::weak_ptr<ctoot::control::ControlLaw> ATTACK_LAW();
				static std::weak_ptr<ctoot::control::ControlLaw> RELEASE_LAW();

			protected:
				ctoot::control::ControlLaw* getAttackLaw() override;
				ctoot::control::ControlLaw* getReleaseLaw() override;
				bool hasGainReductionIndicator() override;
				bool hasDryGain() override;
				bool hasGain() override;
				bool hasKnee() override;
				bool hasInverseRatio() override;
				bool hasRMS() override;

			public:
				BusCompressorControls();
				BusCompressorControls(std::string name, int32_t idOffset);

			};

		}
	}
}
