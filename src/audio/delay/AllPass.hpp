#pragma once


namespace ctoot {
	namespace audio {
		namespace delay {

			class PhaserProcess;

			class AllPass
				
			{

			private:
				float zm1{ 0.0f };

			public:
				virtual float update(float in);
				
				AllPass(PhaserProcess *PhaserProcess_this);				

			private:
				PhaserProcess *PhaserProcess_this;
			};

		}
	}
}
