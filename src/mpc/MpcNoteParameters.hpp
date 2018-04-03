#pragma once

#include <memory>

namespace ctoot {
	namespace mpc {

		class MpcNoteParameters {

		public:
			virtual int getSndNumber() = 0;
			virtual int getSoundGenerationMode() = 0;
			virtual int getOptionalNoteA() = 0;
			virtual int getOptionalNoteB() = 0;
			virtual int getMuteAssignA() = 0;
			virtual int getMuteAssignB() = 0;
			virtual int getTune() = 0;
			virtual int getVelocityToStart() = 0;
			virtual int getAttack() = 0;
			virtual int getDecay() = 0;
			virtual int getVelocityToAttack() = 0;
			virtual int getDecayMode() = 0;
			virtual int getVeloToLevel() = 0;
			virtual int getFilterFrequency() = 0;
			virtual int getVelocityToFilterFrequency() = 0;
			virtual int getFilterAttack() = 0;
			virtual int getFilterDecay() = 0;
			virtual int getFilterResonance() = 0;
			virtual int getFilterEnvelopeAmount() = 0;
			virtual int getVoiceOverlap() = 0;

		};
	}
}
