#pragma once

namespace ctoot {
	namespace synth {

		struct MidiChannel
		{

			virtual void allNotesOff() = 0;

            virtual void controlChange(int controller, int value) = 0;

            virtual int getController(int controller) = 0;

            virtual int getProgram() = 0;

            virtual void noteOff(int noteNumber) = 0;
			virtual void noteOff(int noteNumber, int velocity) = 0;
			virtual void noteOn(int noteNumber, int velocity) = 0;
			virtual void programChange(int program) = 0;
			virtual void programChange(int bank, int program) = 0;

            virtual void setMono(bool on) = 0;

        };
	}
}
