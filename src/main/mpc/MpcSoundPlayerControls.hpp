#pragma once
#include <synth/SynthChannelControls.hpp>
#include <audio/server/AudioServer.hpp>
#include <audio/mixer/AudioMixer.hpp>

#include <memory>

namespace ctoot {

	namespace mpc {
		class MpcMixerSetupGui;
		class MpcSampler;		
		class MpcVoice;
		class MpcMultiMidiSynth;

		class MpcSoundPlayerControls
			: public ctoot::synth::SynthChannelControls
		{

		private:
			std::weak_ptr<MpcMultiMidiSynth> mms;

		public:
			typedef ctoot::synth::SynthChannelControls super;

		public:
			static const int MPC_SOUND_PLAYER_CHANNEL_ID{ 8 };

		private:
			static std::string NAME_;
			std::weak_ptr<ctoot::mpc::MpcSampler> sampler{};
			std::weak_ptr<ctoot::audio::mixer::AudioMixer> mixer{};
			int drumNumber{ 0 };
			std::weak_ptr<ctoot::audio::server::AudioServer> server{ };
			ctoot::mpc::MpcMixerSetupGui* mixerSetupGui;
			
		public:
			std::weak_ptr<MpcMultiMidiSynth> getMms();
			std::weak_ptr<ctoot::mpc::MpcSampler> getSampler();
			int getDrumNumber();
			std::weak_ptr<ctoot::audio::mixer::AudioMixer> getMixer();
			ctoot::audio::server::AudioServer* getServer();
			ctoot::mpc::MpcMixerSetupGui* getMixerSetupGui();

		public:
			MpcSoundPlayerControls(std::weak_ptr<MpcMultiMidiSynth> mms, std::weak_ptr<MpcSampler> sampler, int drumNumber, std::weak_ptr<ctoot::audio::mixer::AudioMixer> mixer, std::weak_ptr<ctoot::audio::server::AudioServer> server, MpcMixerSetupGui* mixerSetupGui);
			MpcSoundPlayerControls();
			~MpcSoundPlayerControls();

		public:
			static std::string NAME();

		};
		REGISTER_TYPE(ctoot::mpc::, MpcSoundPlayerControls)
	}
}
