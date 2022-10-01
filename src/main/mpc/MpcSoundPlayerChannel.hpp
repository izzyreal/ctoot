#pragma once
#include <synth/SynthChannel.hpp>

#include <map>

namespace ctoot::control {
	class CompoundControl;
}

namespace ctoot::audio::server {
	class AudioServer;
}

namespace ctoot::audio::core {
	class MetaInfo;
}

namespace ctoot::audio::mixer {
	class AudioMixer;
	class MainMixControls;
}

namespace ctoot::mpc {
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
}

namespace ctoot::mpc
{
	class MpcSoundPlayerChannel final
		: public ctoot::synth::SynthChannel
	{

	private:
		std::map<int, int> simultA;
		std::map<int, int> simultB;
		std::weak_ptr<MpcSoundPlayerControls> controls;
		std::weak_ptr<MpcSampler> sampler;
		std::weak_ptr<ctoot::audio::mixer::AudioMixer> mixer;
		std::vector<MpcMixerInterconnection*> mixerConnections;
		ctoot::audio::server::AudioServer* server = nullptr;

	private:
		int drumIndex = 0;
		int programNumber = 0;
		bool receivePgmChange = false;
		bool receiveMidiVolume = false;
		int lastReceivedMidiVolume = 127;
		std::vector<std::shared_ptr<MpcStereoMixerChannel>> stereoMixerChannels;
        std::vector<std::weak_ptr<MpcStereoMixerChannel>> weakStereoMixerChannels;
		std::vector<std::shared_ptr<MpcIndivFxMixerChannel>> indivFxMixerChannels;
        std::vector<std::weak_ptr<MpcIndivFxMixerChannel>> weakIndivFxMixerChannels;

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
		void setLastReceivedMidiVolume(int volume);
		int getLastReceivedMidiVolume();
		void mpcNoteOn(int track, int note, int velo, int varType, int varValue, int frameOffset, bool firstGeneration);
        
	public:
		void allSoundOff(int frameOffset);
		void connectVoices();
		std::weak_ptr<ctoot::audio::core::MetaInfo> getInfo();
		std::vector<std::weak_ptr<MpcStereoMixerChannel>> getStereoMixerChannels();
		std::vector<std::weak_ptr<MpcIndivFxMixerChannel>> getIndivFxMixerChannels();
		int getDrumNumber();

	public:
		void mpcNoteOff(int note, int frameOffset);

	private:
        void checkForMutes(MpcNoteParameters* np);
        void startDecayForNote(const int note,
                               const int voiceOverlapMode);
        void startDecayForNote(const int note,
                               const int voiceOverlapMode,
                               const int frameOffset);
        void stopMonoOrPolyVoiceWithSameNoteParameters(ctoot::mpc::MpcNoteParameters* noteParameters, int note);

	public:
		MpcSoundPlayerChannel(std::weak_ptr<MpcSoundPlayerControls> controls);
		~MpcSoundPlayerChannel();

	};
}
