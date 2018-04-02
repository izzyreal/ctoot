#pragma once

#include <memory>

namespace ctoot {
	namespace mpc {

		class MpcProgram {

		public:
			virtual int getPadNumberFromNote(int note) = 0;
			virtual MpcNoteParameters* getNoteParameters(int i) = 0;
			virtual std::weak_ptr<MpcStereoMixerChannel> getStereoMixerChannel(int pad) = 0;
			virtual std::weak_ptr<MpcIndivFxMixerChannel> getIndivFxMixerChannel(int pad) = 0;

		};
	}
}
