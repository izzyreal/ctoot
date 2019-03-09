#pragma once

//#include <misc/Tempo_Listener.hpp>

namespace ctoot {
	namespace audio {
		namespace delay {

			class TempoDelayProcess;

			class TempoDelayProcess1
				//: public virtual ctoot::misc::Tempo_Listener
			{

			public:
				//void tempoChanged(float newTempo) override;

				TempoDelayProcess1(TempoDelayProcess *TempoDelayProcess_this);
				
				TempoDelayProcess *TempoDelayProcess_this;

			};

		}
	}
}
