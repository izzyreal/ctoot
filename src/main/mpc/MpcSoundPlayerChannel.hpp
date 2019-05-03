#pragma once
#include <synth/SynthChannel.hpp>

#include <map>

namespace ctoot {

	namespace control {
		class CompoundControl;
	}

	namespace audio {

		namespace server {
			class AudioServer;
		}

		namespace core {
			class MetaInfo;
		}

		namespace mixer {
			class AudioMixer;
			class MainMixControls;
		}
	}
}

namespace ctoot {

	namespace mpc {
		class MpcSampler;
		class MpcStereoMixerChannel;
		class MpcIndivFxMixerChannel;
		class MpcProgram;
		class MpcNoteParameters;
		class MpcSound;
		class MpcVoice;
		class MpcSoundPlayerControls;
		class MpcFaderControl;
		class MpcMixerInterconnection;
		class MpcSoundPlayerChannel final
			: public ctoot::synth::SynthChannel
		{

		private:
			std::map<int, int> simultA;
			std::map<int, int> simultB;
			std::weak_ptr<MpcSoundPlayerControls> controls{};
			std::weak_ptr<ctoot::mpc::MpcSampler> sampler{};
			std::weak_ptr<ctoot::audio::mixer::AudioMixer> mixer{};
			std::vector<MpcMixerInterconnection*> mixerConnections{};
			ctoot::audio::server::AudioServer* server{ nullptr };

		private:
			int index{ 0 };
			int programNumber{ 0 };
			bool receivePgmChange{ false };
			bool receiveMidiVolume{ false };
			std::vector<std::shared_ptr<ctoot::mpc::MpcStereoMixerChannel>> stereoMixerChannels;
			std::vector<std::shared_ptr<ctoot::mpc::MpcIndivFxMixerChannel>> indivFxMixerChannels;

		public:
			int getProgram() override;
			void setLocation(std::string location) override;
			void noteOn(int note, int velo) override;
			void noteOff(int note) override;
			void allNotesOff() override;
			void allSoundOff() override;

		public:
			void setProgram(int i);
			bool receivesPgmChange();
			void setReceivePgmChange(bool b);
			bool receivesMidiVolume();
			void setReceiveMidiVolume(bool b);
			void mpcNoteOn(int track, int note, int velo, int varType, int varValue, int frameOffset, bool firstGeneration);

		private:
			void checkForMutes(ctoot::mpc::MpcNoteParameters* np);
			void stopPad(int p, int o);

		public:
			void allSoundOff(int frameOffset);
			void connectVoices();
			std::weak_ptr<ctoot::audio::core::MetaInfo> getInfo();
			std::vector<std::weak_ptr<ctoot::mpc::MpcStereoMixerChannel>> getStereoMixerChannels();
			std::vector<std::weak_ptr<ctoot::mpc::MpcIndivFxMixerChannel>> getIndivFxMixerChannels();
			int getDrumNumber();

		public:
			void mpcNoteOff(int note, int frameOffset);

		private:
			void stopPad(int p, int o, int offset);

		public:
			MpcSoundPlayerChannel(std::weak_ptr<MpcSoundPlayerControls> controls);
			~MpcSoundPlayerChannel();

		};
	}
}
