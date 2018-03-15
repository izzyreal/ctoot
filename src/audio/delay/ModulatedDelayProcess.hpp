#pragma once

#include <audio/core/AudioProcess.hpp>

#include <memory>
#include <vector>

namespace ctoot {
	namespace audio {
		namespace delay {
			
			class DelayBuffer;
			class ModulatedDelayProcessVariables;

			class ModulatedDelayProcess
				: public virtual ctoot::audio::core::AudioProcess
			{

			private:
				DelayBuffer* delayBuffer{  };
				ModulatedDelayProcessVariables* vars{  };

			protected:
				std::vector<int> modulatorMap{  };
				float modulatorPhase{  }, modulatorPhaseQuad{  };

			private:
				bool phaseQuad{  };
				std::vector<std::vector<float>*> samples{  };

			protected:
				std::weak_ptr<ctoot::audio::core::ChannelFormat> format;

			private:
				bool wasBypassed{  };

			public:
				void open() override;
				int processAudio(ctoot::audio::core::AudioBuffer* buffer) override;
				void close() override;

			protected:
				virtual void buildModulatorMap(ctoot::audio::core::AudioBuffer* buffer);
				virtual void incrementModulators(float timeDelta);
				virtual float modulation(int chan);
				virtual int msToSamples(float ms, float sr);

			public:
				ModulatedDelayProcess(ModulatedDelayProcessVariables* vars);

			};

		}
	}
}
