#pragma once

#include <audio/core/AudioControls.hpp>

#include <audio/core/ChannelFormat.hpp>

#include <control/LinearLaw.hpp>

#include <memory>
#include <vector>
#include <string>

namespace ctoot {
	namespace audio {
		namespace meter {

			class TypeControl;
			class MindBControl;

			struct ChannelState {
				int overs{};
				float maxPeak{};
				float peak{};
				float maxAverage{};
				float average{};
			};

			class MeterControls
				: public ctoot::audio::core::AudioControls
			{

			public:
				static constexpr int METER{ 100 };
				static constexpr int METER_TYPE{ 2 };
				static constexpr int METER_RESET{ 3 };
				static constexpr int METER_OVERS{ 4 };
				static constexpr int METER_INDICATOR{ 5 };
				static constexpr int METER_MIN_DB{ 6 };

			public:
				static std::weak_ptr<ctoot::control::LinearLaw> METER_LAW();
			
			private:
				std::weak_ptr<ctoot::audio::core::ChannelFormat> channelFormat;
				std::vector<ChannelState> channelState{  };
				std::weak_ptr<TypeControl> typeControl{  };
				std::weak_ptr<MindBControl> mindBControl{  };
				float peakRelease{ 0.005f };
				float averageSmooth{ 0.038f };
				float maxdB{ 20.0f }, mindB{ -80.0f };

			protected:
				void derive(ctoot::control::Control* c) override;

			public:
				bool canBypass() override;
				bool isAlwaysVertical() override;
				float getMaxdB();
				float getMindB();
				std::weak_ptr<ctoot::audio::core::ChannelFormat> getChannelFormat();

			protected:
				bool invalidChannel(int chan);

			public:
				ChannelState getState(int chan);
				void resetOvers();
				void resetMaxima();
				void addOvers(int chan, int overs);
				void setPeak(int chan, float peak);
				void setAverage(int chan, float average);

			private:
				static double PEAK_K_PER_MS_;
				static double AV_K_PER_MS_;

			public:
				void setUpdateTime(float ms);

				MeterControls(std::weak_ptr<ctoot::audio::core::ChannelFormat> format, std::string name);
				MeterControls(std::weak_ptr<ctoot::audio::core::ChannelFormat> format, std::string name, bool full);

			private:
				static double PEAK_K_PER_MS();
				static double AV_K_PER_MS();

			};

		}
	}
}
