#pragma once

namespace ctoot {
	namespace mpc {

		class MpcMuteInfo
		{

		private:
			int note{ 0 };
			int drum{ 0 };

		public:
			void setNote(int note);
			void setDrum(int drum);
			int getNote();
			int getDrum();
			bool muteMe(int note, int drum);

			MpcMuteInfo();

		};

	}
}
