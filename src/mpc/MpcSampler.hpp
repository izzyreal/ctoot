#pragma once

#include <memory>

namespace ctoot {
	namespace mpc {

		class MpcSound;
		class MpcProgram;

		class MpcSampler {

		public:
			virtual std::weak_ptr<MpcSound> getPreviewSound() = 0;
			virtual std::weak_ptr<MpcSound> getPlayXSound() = 0;
			virtual std::weak_ptr<MpcSound> getClickSound() = 0;
			virtual std::weak_ptr<MpcSound> getSound(int soundNumber) = 0;
			virtual std::weak_ptr<MpcProgram> getProgram(int i) = 0;

		};
	}
}
