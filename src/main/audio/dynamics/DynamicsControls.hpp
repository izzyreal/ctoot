#pragma once

#include <audio/core/AudioControls.hpp>
#include <audio/dynamics/DynamicsVariables.hpp>

#include <memory>

namespace ctoot {

	namespace control {
		class EnumControl;
		class ControlLaw;
		class FloatControl;
		class BooleanControl;
	}

	namespace audio {

		namespace core {
			class TapControl;
		}

		namespace dynamics {

			class GainReductionIndicator;

			class DynamicsControls
				: public ctoot::audio::core::AudioControls
				, public virtual DynamicsVariables
			{

			private:
				static std::weak_ptr<ctoot::control::ControlLaw> THRESH_LAW();
				static std::weak_ptr<ctoot::control::ControlLaw> RATIO_LAW();
				static std::weak_ptr<ctoot::control::ControlLaw> INVERSE_RATIO_LAW();
				static std::weak_ptr<ctoot::control::ControlLaw> KNEE_LAW();
				static std::weak_ptr<ctoot::control::ControlLaw> ATTACK_LAW();
				static std::weak_ptr<ctoot::control::ControlLaw> HOLD_LAW();
				static std::weak_ptr<ctoot::control::ControlLaw> RELEASE_LAW();
				static std::weak_ptr<ctoot::control::ControlLaw> DRY_GAIN_LAW();
				static std::weak_ptr<ctoot::control::ControlLaw> WET_GAIN_LAW();
				static std::weak_ptr<ctoot::control::ControlLaw> GAIN_LAW();
				static std::weak_ptr<ctoot::control::ControlLaw> DEPTH_LAW();
				static std::weak_ptr<ctoot::control::ControlLaw> HYSTERESIS_LAW();
				static std::weak_ptr<ctoot::control::ControlLaw> INPUT_GAIN_LAW();
				static std::weak_ptr<ctoot::control::ControlLaw> OUTPUT_GAIN_LAW();
				static std::weak_ptr<ctoot::control::ControlLaw> LOOK_AHEAD_LAW();


				std::weak_ptr<GainReductionIndicator> gainReductionIndicator{};
				std::weak_ptr<ctoot::control::FloatControl> thresholdControl{};
				std::weak_ptr<ctoot::control::FloatControl> ratioControl{};
				std::weak_ptr<ctoot::control::FloatControl> kneeControl{};
				std::weak_ptr<ctoot::control::BooleanControl> rmsControl{};
				std::weak_ptr<ctoot::control::FloatControl> attackControl{};
				std::weak_ptr<ctoot::control::FloatControl> holdControl{};
				std::weak_ptr<ctoot::control::FloatControl> releaseControl{};
				std::weak_ptr<ctoot::control::FloatControl> dryGainControl{};
				std::weak_ptr<ctoot::control::FloatControl> wetGainControl{};
				std::weak_ptr<ctoot::control::FloatControl> gainControl{};
				std::weak_ptr<ctoot::control::FloatControl> depthControl{};
				std::weak_ptr<ctoot::control::FloatControl> hysteresisControl{};
				std::weak_ptr<ctoot::audio::core::TapControl> keyControl{};
				std::weak_ptr<ctoot::control::EnumControl> detectionChannelControl{};
				std::weak_ptr<ctoot::control::EnumControl> attenuationChannelControl{};
				std::weak_ptr<ctoot::control::FloatControl> inputGainControl;
				std::weak_ptr<ctoot::control::FloatControl> outputGainControl;
				std::weak_ptr<ctoot::control::FloatControl> lookAheadControl;
				std::weak_ptr<ctoot::control::BooleanControl> muteControl;
				std::weak_ptr<ctoot::control::BooleanControl> soloControl;

				float sampleRate{ 44100.0f };
				float threshold{}, inverseThreshold{}, thresholddB{}, inverseRatio{}, kneedB{ 10.0f };
				float attack{}, release{}, gain{ 1.0f }, dryGain{ 0.0f }, wetGain{ 0.0f }, depth{ 40.0f }, hysteresis{ 0.0f }, inputGain{ 1.0f }, outputGain{ 1.0f };
				float lookAhead{ 0.0f };
				bool mute{ false }, solo{ false };
				std::string detectionChannelMode;
				std::string attenuationChannelMode;
				bool rms{ false };

			public:
				int32_t hold{ 0 };

			private:
				ctoot::audio::core::AudioBuffer* key{};
				int32_t idOffset{ 0 };

			public:
				void update(float sampleRate) override;
			
			protected:
				void init();

			private:
				bool initialized = false;

			protected:
				void derive(ctoot::control::Control* c) override;
				virtual void deriveThreshold();
				virtual void deriveRatio();
				virtual void deriveKnee();
				virtual void deriveRMS();

			private:
				static float& LOG_0_01();

			protected:
				virtual float deriveTimeFactor(float milliseconds);
				virtual void deriveAttack();
				virtual void deriveHold();
				virtual void deriveRelease();
				virtual void deriveDryGain();
				virtual void deriveWetGain();
				virtual void deriveGain();
				virtual void deriveDepth();
				virtual void deriveHysteresis();
				virtual void deriveKey();
				virtual void deriveDetectionChannelMode();
				virtual void deriveAttenuationChannelMode();
				virtual void deriveInputGain();
				virtual void deriveOutputGain();
				virtual void deriveLookAhead();
				virtual void deriveMute();
				virtual void deriveSolo();

				void setParent(ctoot::control::CompoundControl* parent) override;
				virtual std::weak_ptr<ctoot::control::ControlLaw> getThresholdLaw();
				virtual std::weak_ptr<ctoot::control::ControlLaw> getAttackLaw();
				virtual std::weak_ptr<ctoot::control::ControlLaw> getHoldLaw();
				virtual std::weak_ptr<ctoot::control::ControlLaw> getReleaseLaw();
				virtual std::weak_ptr<ctoot::control::ControlLaw> getDryGainLaw();
				virtual std::weak_ptr<ctoot::control::ControlLaw> getWetGainLaw();
				virtual std::weak_ptr<ctoot::control::ControlLaw> getGainLaw();
				virtual std::weak_ptr<ctoot::control::ControlLaw> getDepthLaw();
				virtual std::weak_ptr<ctoot::control::ControlLaw> getHysteresisLaw();
				virtual std::weak_ptr<ctoot::control::ControlLaw> getLookAheadLaw();

				virtual bool hasKey();
				virtual bool hasHysteresis();
				virtual bool hasDepth();
				virtual bool hasGain();
				virtual bool hasGainReductionIndicator();
				virtual bool hasInverseRatio();
				virtual bool hasRatio();
				virtual bool hasKnee();
				virtual bool hasRMS();
				virtual bool hasHold();
				virtual bool hasDryGain();
				virtual bool hasWetGain();
				virtual bool hasChannelMode();
				virtual bool hasInputGain();
				virtual bool hasOutputGain();
				virtual bool hasLookAhead();
				virtual bool hasMute();
				virtual bool hasSolo();

				virtual std::shared_ptr<ctoot::control::FloatControl> createDepthControl();
				virtual std::shared_ptr<ctoot::control::FloatControl> createGainControl();
				virtual std::shared_ptr<ctoot::control::FloatControl> createDryGainControl();
				virtual std::shared_ptr<ctoot::control::FloatControl> createWetGainControl();
				virtual std::shared_ptr<ctoot::control::FloatControl> createThresholdControl();
				virtual std::shared_ptr<ctoot::control::FloatControl> createRatioControl();
				virtual std::shared_ptr<ctoot::control::FloatControl> createKneeControl();
				virtual std::shared_ptr<ctoot::control::BooleanControl> createRMSControl();
				virtual std::shared_ptr<ctoot::control::FloatControl> createAttackControl();
				virtual std::shared_ptr<ctoot::control::FloatControl> createHoldControl();
				virtual std::shared_ptr<ctoot::control::FloatControl> createReleaseControl();
				virtual std::shared_ptr<ctoot::control::FloatControl> createHysteresisControl();
				virtual std::shared_ptr<ctoot::audio::core::TapControl> createKeyControl();
				virtual std::shared_ptr<ctoot::control::EnumControl> createDetectionChannelControl();
				virtual std::shared_ptr<ctoot::control::EnumControl> createAttenuationChannelControl();
				virtual std::shared_ptr<ctoot::control::FloatControl> createInputGainControl();
				virtual std::shared_ptr<ctoot::control::FloatControl> createOutputGainControl();
				virtual std::shared_ptr<ctoot::control::FloatControl> createLookAheadControl();
				virtual std::shared_ptr<ctoot::control::BooleanControl> createMuteControl();
				virtual std::shared_ptr<ctoot::control::BooleanControl> createSoloControl();

			public:
				float getThreshold() override;
				float getInverseThreshold() override;
				float getThresholddB() override;
				float getKneedB() override;
				float getInverseRatio() override;
				float getAttack() override;
				int32_t getHold() override;
				float getRelease() override;
				float getDryGain() override;
				float getWetGain() override;
				float getGain() override;
				float getDepth() override;
				float getHysteresis() override;
				ctoot::audio::core::AudioBuffer* getKeyBuffer() override;
				bool isRMS() override;
				void setDynamicGain(float dynamicGain) override;
				std::string getDetectionChannelMode() override;
				std::string getAttenuationChannelMode() override;
				float getInputGain() override;
				float getOutputGain() override;
				float getLookAhead() override;
				bool getMute() override;
				bool getSolo() override;

			protected:
				virtual std::weak_ptr<ctoot::control::ControlLaw> getInverseRatioLaw();

			public:
				static std::vector<std::string> ratioPresets2;

			public:
				DynamicsControls(int32_t id, std::string name);
				DynamicsControls(int32_t id, std::string name, int32_t idOffset);

			public:
				virtual bool isBypassed();

			private:
				friend class InverseRatioControl;

			};
		}
	}
}
