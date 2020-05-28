#pragma once

#include <memory>

namespace ctoot {
	namespace mpc {

		class MpcNoteParameters;
		class MpcStereoMixerChannel;
		class MpcIndivFxMixerChannel;

		class MpcProgram {

		public:
			virtual int getPadIndexFromNote(int note) = 0;
			virtual MpcNoteParameters* getNoteParameters(int i) = 0;
			virtual std::weak_ptr<MpcStereoMixerChannel> getStereoMixerChannel(int pad) = 0;
			virtual std::weak_ptr<MpcIndivFxMixerChannel> getIndivFxMixerChannel(int pad) = 0;

		};
	}
}
