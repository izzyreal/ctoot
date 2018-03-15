#pragma once

#include <audio/core/AudioControls.hpp>
#include <audio/delay/WowFlutterProcessVariables.hpp>
#include <audio/delay/TapeSpeedControl.hpp>
#include <control/FloatControl.hpp>

#include <vector>
#include <string>
#include <memory>

namespace ctoot {
	namespace audio {
		namespace delay {

			class WowFlutterControls
				: public ctoot::audio::core::AudioControls
				, public virtual WowFlutterProcessVariables
			{

			public:
				typedef ctoot::audio::core::AudioControls super;

				static constexpr int SPEED{ 0 };

			private:
				int fuid{ -1 };
				static constexpr int LEVEL{ 1 };
				std::weak_ptr<TapeSpeedControl> speedControl{};
				std::weak_ptr<ctoot::control::FloatControl> levelControl{};
				float level{};
				std::vector<float> amplitudes{};
				std::vector<float> frequencies{};
				std::vector<float> nextAmps{};
				std::vector<float> nextFreqs{};

			public:
				void derive(ctoot::control::Control* c) override;
				virtual std::shared_ptr<ctoot::control::FloatControl> createLevelControl();
				virtual void speedChanged(float ips);

			public:
				float getLevel() override;
				std::vector<float> getAmplitudes() override;
				int getFrequencyUid() override;
				std::vector<float> getFrequencies() override;
				float getMaxDelayMilliseconds() override;

			private:
				static std::vector<float> diameters();

			public:
				static std::vector<std::string> speeds();

			public:
				WowFlutterControls();

			public:
				virtual bool isBypassed();
			};
			REGISTER_TYPE(ctoot::audio::delay::, WowFlutterControls)
		}
	}
}
