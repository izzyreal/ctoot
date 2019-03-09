#pragma once

#include <audio/core/AudioControls.hpp>
#include <audio/core/ChannelFormat.hpp>
#include <audio/mixer/SoloIndicator.hpp>
#include <audio/meter/MeterControls.hpp>

#include <observer/Observer.hpp>

#include <string>
#include <memory>

namespace ctoot {
	namespace audio {
		namespace mixer {

			class BusControls
				: public virtual ctoot::audio::core::AudioControls
				, public moduru::observer::Observer
			{

			private:
				SoloIndicator* soloIndicator{ nullptr };
				std::weak_ptr<ctoot::audio::meter::MeterControls> meterControls;
				int soloCount{ 0 };
				std::weak_ptr<ctoot::audio::core::ChannelFormat> channelFormat;

			public:
				SoloIndicator* getSoloIndicator();
				std::weak_ptr<ctoot::audio::meter::MeterControls> getMeterControls();
				virtual bool hasSolo();
				virtual std::weak_ptr<ctoot::audio::core::ChannelFormat> getChannelFormat();
				virtual void update(moduru::observer::Observable* o, std::any a) override;
				bool canBypass() override;
				std::string toString();

			public:
				BusControls(int id, std::string name, std::weak_ptr<ctoot::audio::core::ChannelFormat> format);
				virtual ~BusControls();
			};

		}
	}
}
