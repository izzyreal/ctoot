#pragma once

#include <audio/core/AudioControls.hpp>
#include <audio/mixer/MixVariables.hpp>
#include <audio/fader/FaderControl.hpp>
#include <audio/mixer/BusControls.hpp>
#include <audio/mixer/SoloIndicator.hpp>
#include <audio/mixer/MixerControls.hpp>
#include <control/EnumControl.hpp>

namespace ctoot {
	namespace audio {
		namespace mixer {

			class LCRControl;
			class FrontRearControl;

			class MixControls
            : public virtual MixVariables
			, public ctoot::audio::core::AudioControls

			{

			private:
				static float HALF_ROOT_TWO_;

			private:
				std::shared_ptr<ctoot::control::BooleanControl> soloControl{ nullptr };
				std::shared_ptr<ctoot::control::BooleanControl> muteControl{ nullptr };
				std::shared_ptr<ctoot::audio::fader::FaderControl> gainControl{ nullptr };
				std::shared_ptr<LCRControl> lcrControl { nullptr } ;
				std::shared_ptr<FrontRearControl> frontRearControl{ nullptr };
				std::weak_ptr<BusControls> busControls{ };

			protected:
				MixerControls* mixerControls{ nullptr };
				
			public:
				MixerControls* getMixerControls();

			private:
				bool  master { false };
				int channelCount{ 0 };
				bool mute{ false }, solo{ false };
				float gain{ 0 }, left{ 0 }, right{ 0 }, front{ 0 }, rear{ 0 };

			public:
				void derive(Control* c) override;

			public:
				virtual ctoot::control::BooleanControl* getSoloControl();
				virtual ctoot::control::BooleanControl* getMuteControl();

			public:
				bool isMaster() override;
                std::weak_ptr<ctoot::audio::core::ChannelFormat> getChannelFormat() override;
				bool canBypass() override;
				bool isAlwaysVertical() override;
				bool canBeDeleted() override;
				bool hasPresets() override;
				virtual bool isSolo();
				virtual bool isMute();
				bool isEnabled() override;
				virtual bool hasSolo();
				float getGain() override;
				void getChannelGains(std::vector<float>* dest) override;
				float getSmoothingFactor() override;

			public:
				virtual ctoot::control::EnumControl* createRouteControl(int stripId);
				virtual ctoot::control::BooleanControl* createMuteControl();
				virtual ctoot::control::BooleanControl* createSoloControl();

			public:
				MixControls(MixerControls* mixerControls, int stripId, std::weak_ptr<BusControls> busControls, bool isMaster);
				~MixControls();

			public:
				virtual std::string getName();

			public:
				static float& HALF_ROOT_TWO();
			};
		}
	}
}
