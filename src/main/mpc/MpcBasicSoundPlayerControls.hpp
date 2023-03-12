#pragma once
#include <synth/SynthChannelControls.hpp>
#include <audio/mixer/AudioMixer.hpp>

#include <memory>

namespace ctoot {

	namespace mpc {
		class MpcSampler;
		class MpcVoice;
		class MpcSoundOscillatorControls;
		class MpcEnvelopeControls;

		class MpcBasicSoundPlayerControls
			: public ctoot::synth::SynthChannelControls
		{

		public:
			typedef ctoot::synth::SynthChannelControls super;

		public:
			static const int MPC_BASIC_SOUND_PLAYER_CHANNEL_ID{ 9 };

		private:
			static std::string NAME_;

        private:
			std::weak_ptr<ctoot::mpc::MpcSampler> sampler{ };
			std::weak_ptr<ctoot::mpc::MpcVoice> voice{};
			std::weak_ptr<ctoot::audio::mixer::AudioMixer> mixer{};

		public:
			std::weak_ptr<ctoot::mpc::MpcSampler> getSampler();
			std::weak_ptr<ctoot::audio::mixer::AudioMixer> getMixer();
			std::weak_ptr<ctoot::mpc::MpcVoice> getVoice();

			MpcBasicSoundPlayerControls(std::weak_ptr<ctoot::mpc::MpcSampler> sampler, std::shared_ptr<ctoot::audio::mixer::AudioMixer> mixer, std::weak_ptr<ctoot::mpc::MpcVoice> voice);
			MpcBasicSoundPlayerControls();
			~MpcBasicSoundPlayerControls();

		public:
			static std::string& NAME();

		};
	}
}
