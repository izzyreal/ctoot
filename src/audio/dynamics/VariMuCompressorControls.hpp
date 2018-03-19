#pragma once
#include <audio/dynamics/DynamicsControls.hpp>

namespace ctoot {
	namespace audio {
		namespace dynamics {

			class VariMuCompressorControls
				: public DynamicsControls
			{

			private:
				static std::weak_ptr<ctoot::control::ControlLaw> RELEASE_LAW();

			protected:
				ctoot::control::ControlLaw* getReleaseLaw() override;
				bool hasGainReductionIndicator() override;
				bool hasDryGain() override;
				bool hasGain() override;

			public:
				bool isRMS() override;

				VariMuCompressorControls();
				VariMuCompressorControls(std::string name, int32_t idOffset);

			};

		}
	}
}
