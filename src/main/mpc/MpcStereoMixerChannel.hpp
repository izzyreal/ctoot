#pragma once

#include <observer/Observable.hpp>

namespace ctoot {
	namespace mpc {

		class MpcStereoMixerChannel
			: public moduru::observer::Observable
		{

		private:
			int panning{ 0 };
			int level{ 0 };
			bool stereo{ false };

		public:
			void setStereo(bool b);
			bool isStereo();
			void setPanning(int i);
			int getPanning();
			void setLevel(int i);
			int getLevel();

		public:
			MpcStereoMixerChannel();
            virtual ~MpcStereoMixerChannel() {}
            
		};
	}
}
