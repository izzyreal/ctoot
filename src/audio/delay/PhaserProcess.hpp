#pragma once

#include <audio/core/SimpleAudioProcess.hpp>

#include <vector>

namespace ctoot {
	namespace audio {
		namespace delay {
			
			class AllPass;
			class PhaserProcessVariables;

			class PhaserProcess
				: public ctoot::audio::core::SimpleAudioProcess
			{

			public:
				float a1{};

			private:
				static constexpr int N{ 12 };
				std::vector<AllPass*> allpass{  };
				float zm1{  };
				float lfoPhase{  };
				float dmin{  }, dmax{  };
				int sampleRate{  };
				PhaserProcessVariables* vars{  };

			public:
				int processAudio(ctoot::audio::core::AudioBuffer* buffer) override;

			public:
				PhaserProcess(PhaserProcessVariables* vars);
				~PhaserProcess();
			};

		}
	}
}
