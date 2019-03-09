#pragma once

#include <audio/dynamics/DynamicsControls.hpp>

#include <memory>

namespace ctoot {

	namespace control {
		class ControlLaw;
	}

	namespace audio {
		namespace dynamics {

			class CompressorControls
				: public DynamicsControls
			{

			private:
				static std::weak_ptr<ctoot::control::ControlLaw> ATTACK_LAW();

			protected:
				std::weak_ptr<ctoot::control::ControlLaw> getAttackLaw() override;
				bool hasGainReductionIndicator() override;
				bool hasRatio() override;
				bool hasGain() override;
				bool hasDryGain() override;
				bool hasKey() override;

			public:
				CompressorControls();
				CompressorControls(std::string name, int32_t idOffset);

			};
			REGISTER_TYPE(ctoot::audio::dynamics::, CompressorControls)
		}
	}
}
