#pragma once

#include <audio/core/SimpleAudioProcess.hpp>

#include <vector>

namespace ctoot {
	namespace audio {
		namespace dynamics {

			class TremoloProcess
				: public ctoot::audio::core::SimpleAudioProcess
			{

			private:
				TremoloProcessVariables * vars{  };
				std::vector<std::vector<float>*> samples{  };
				float lfoPhase{  };

			public:
				int32_t processAudio(ctoot::audio::core::AudioBuffer* buffer) override;

				TremoloProcess(TremoloProcessVariables* variables);

			private:
				void init();
			};

		}
	}
}
