#pragma once

#include <audio/core/AudioControls.hpp>
#include <audio/dynamics/izcompressor/IzCompressorProcessVariables.hpp>

#include <audio/dynamics/izcompressor/ChannelControl.hpp>

#include <memory>
#include <vector>

namespace ctoot {

	namespace control {
		class Control;
	}

	namespace audio {
		namespace dynamics {
			namespace izcompressor {

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
					std::string detectionChannelMode;
					std::string attenuationChannelMode;
					float inputGain;
					float outputGain;
					float lookAhead;
					bool mute;
					float dryGain;
					float wetGain;

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
					std::string getDetectionChannelMode() override;
					std::string getAttenuationChannelMode() override;
					float getInputGain() override;
					float getOutputGain() override;
					float getLookAhead() override;
					bool getMute() override;
					float getDryGain() override;
					float getWetGain() override;

				public:
					IzBandCompressorControls();
					IzBandCompressorControls(std::string band, int idOffset);

				public:
					virtual bool isBypassed();

				};
				REGISTER_TYPE(ctoot::audio::dynamics::izcompressor:: , IzBandCompressorControls)
			}
		}
	}
}