#pragma once
#include <synth/SynthChannel.hpp>
#include <audio/mixer/AudioMixerStrip.hpp>

#include <memory>

namespace ctoot {
	namespace mpc {

		class MpcSampler;
		class MpcSound;
		class MpcBasicSoundPlayerControls;
		class MpcVoice;

		class MpcBasicSoundPlayerChannel final
			: public ctoot::synth::SynthChannel
		{

		public:
			typedef ctoot::synth::SynthChannel super;

		private:
			std::weak_ptr<ctoot::mpc::MpcSampler> sampler{};
			std::weak_ptr<ctoot::mpc::MpcVoice> voice{};
			std::weak_ptr<ctoot::mpc::MpcSound> tempVars{};

			std::weak_ptr<ctoot::audio::mixer::AudioMixerStrip> mixerStrip{ };
			std::weak_ptr<ctoot::audio::mixer::AudioMixer> mixer{ };
			std::weak_ptr<ctoot::audio::fader::FaderControl> fader;

		public:
			void finishVoice();
			void setLocation(std::string location) override;
			void noteOn(int soundNumber, int velocity) override;
			void mpcNoteOn(int soundNumber, int velocity, int frameOffset);
			void noteOff(int note) override;
			void allNotesOff() override;
			void allSoundOff() override;
			void connectVoice();

			MpcBasicSoundPlayerChannel(std::weak_ptr<MpcBasicSoundPlayerControls> controls);
			~MpcBasicSoundPlayerChannel();

		public:
			void noteOff(int pitch, int velocity) override;

		};

	}
}
