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
				
				AllPass(const PhaserProcess*);
                virtual ~AllPass() {}
                
			private:
				const PhaserProcess* phaserProcess;
			};

		}
	}
}
