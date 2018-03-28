#pragma once

#include <synth/SynthChannel.hpp>
#include <audio/system/AudioOutput.hpp>

#include <memory>

namespace ctoot {
	namespace synth {

		class PolyphonicSynthChannel
			: public SynthChannel
			, public virtual ctoot::audio::system::AudioOutput
		{

		private:
			std::vector<PolyphonicSynthChannelVoice*> voices;
			std::vector<PolyphonicSynthChannelVoice*> finished;
			int32_t polyphony{ 8 };
			std::shared_ptr<ctoot::audio::core::MetaInfo> info{  };
			std::string name{  };
			std::string location{  };

		public:
			std::string getName() override;
			void setLocation(std::string location) override;
			std::string getLocation() override;
			void open() override;
			int32_t processAudio(ctoot::audio::core::AudioBuffer* buffer) override;
			void close() override;
			virtual void setPolyphony(int32_t p);
			virtual int32_t getPolyphony();
			void noteOn(int32_t pitch, int32_t velocity) override;
			void noteOff(int32_t pitch) override;
			void allNotesOff() override;
			void allSoundOff() override;

		protected:
			virtual PolyphonicSynthChannelVoice* createVoice(int32_t pitch, int32_t velocity, int32_t sampleRate) = 0;

		public:
			PolyphonicSynthChannel(std::string name);

		public:
			void noteOff(int32_t pitch, int32_t velocity);

		private:
			friend class PolyphonicSynthChannelVoice;
			friend class PolyphonicSynthChannelAbstractVoice;
		};

	}
}
