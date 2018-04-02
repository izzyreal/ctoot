#pragma once
#include <observer/Observable.hpp>
#include <synth/MidiChannel.hpp>
#include <audio/core/ChannelFormat.hpp>

namespace ctoot {
	namespace synth {

		class SynthChannel
			: public moduru::observer::Observable
			, public virtual MidiChannel
		{

		public:
			int sampleRate{ 44100 };
			float inverseNyquist{ 2.0f / sampleRate };

		private:
			int rawBend{ 8192 };
			int bendRange{ 2 };
			float bendFactor{ 1.0f };
			int pressure{ 0 };
			std::vector<char> polyPressure = std::vector<char>(128);
			std::vector<char> controller = std::vector<char>(128);

			static const double ONE_SEMITONE;
			static std::vector<float> freqTable;

		public:
			virtual void setLocation(std::string location) = 0;

		private:
			static std::vector<float> createFreqTable();

		public:
			static float midiFreq(float pitch);

		private:
			static float midiFreqImpl(int pitch);

		public:
			virtual void setSampleRate(int rate);
			virtual std::weak_ptr<ctoot::audio::core::ChannelFormat> getChannelFormat();
			/*void noteOn(int pitch, int velocity); (already declared) */
			/*void noteOff(int pitch); (already declared) */

		public:
			void noteOff(int pitch, int velocity) override;
			/*void allNotesOff(); (already declared) */
			/*void allSoundOff(); (already declared) */
			void controlChange(int arg0, int arg1) override;
			int getController(int arg0) override;
			void resetAllControllers() override;
			int getProgram() override;
			void programChange(int arg0) override;
			void programChange(int arg0, int arg1) override;
			int getChannelPressure() override;
			void setChannelPressure(int arg0) override;
			int getPolyPressure(int arg0) override;
			void setPolyPressure(int arg0, int arg1) override;
			bool getSolo() override;
			bool getMute() override;
			bool getMono() override;
			bool getOmni() override;
			void setSolo(bool arg0) override;
			void setMute(bool arg0) override;
			void setMono(bool mono) override;
			void setOmni(bool arg0) override;
			bool localControl(bool arg0) override;
			void setPitchBend(int bend) override;
			int getPitchBend() override;
			virtual float getBendFactor();

			SynthChannel();

		public:
			virtual void noteOff(int noteNumber) = 0;

		};
	}
}
