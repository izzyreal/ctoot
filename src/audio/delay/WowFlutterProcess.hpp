#pragma once

#include <audio/delay/FrequencyModulationProcess.hpp>

#include <dsp/Phasor.hpp>

#include <vector>

namespace ctoot {
	namespace audio {
		namespace delay {

			class WowFlutterProcessVariables;

			class WowFlutterProcess
				: public FrequencyModulationProcess
			{

			public:
				typedef FrequencyModulationProcess super;

			private:
				WowFlutterProcessVariables * vars{  };
				float level{  };
				std::vector<float> amplitudes{  };
				std::vector<ctoot::dsp::Phasor*> phasors;
				int fuid{ -1 };

			public:
				void sampleRateChanged() override;
				void cacheProcessVariables() override;
				float modulation() override;

			private:
				void deletePhasors();
				void createPhasors(std::vector<float> frequencies);

			public:
				WowFlutterProcess(WowFlutterProcessVariables* v);
				~WowFlutterProcess();

			};

		}
	}
}
