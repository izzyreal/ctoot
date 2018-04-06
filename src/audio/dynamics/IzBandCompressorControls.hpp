#pragma once

#include <audio/core/AudioControls.hpp>
#include <audio/dynamics/IzCompressorProcessVariables.hpp>

#include <memory>
#include <vector>

namespace ctoot {

	namespace control {
		class Control;
	}

	namespace audio {
		namespace dynamics {

			class IzCompressorControls;

			class IzBandCompressorControls
				: public ctoot::audio::core::AudioControls
				, public virtual IzCompressorProcessVariables
			{

			private:
				std::weak_ptr<IzCompressorControls> compressorControls;
				float threshold;
				float inverseThreshold;
				float knee;
				float inverseRatio;
				float attack;
				int32_t hold;
				float release;
				float gain;
				float depth;

			protected:
				virtual void deriveIndependentVariables();
				virtual void deriveDependentVariables();
				void derive(ctoot::control::Control* c) override;

			public:
				void update(float sampleRate) override;
				float getThreshold() override;
				float getInverseThreshold() override;
				float getKnee() override;
				float getInverseRatio() override;
				float getAttack() override;
				float getRelease() override;
				float getGain() override;
				float getDepth() override;
				void setDynamicGain(float gain) override;

			public:
				IzBandCompressorControls();
				IzBandCompressorControls(std::string band);

			public:
				virtual bool isBypassed();

			};
			REGISTER_TYPE(ctoot::audio::dynamics::, IzBandCompressorControls)
		}
	}
}
