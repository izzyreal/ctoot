#pragma once
#include <audio/core/SimpleAudioProcess.hpp>

namespace ctoot {
	namespace mpc {

		class InterconnectionOutputProcess
			: public ctoot::audio::core::SimpleAudioProcess
		{

		public:
			int processAudio(ctoot::audio::core::AudioBuffer* buffer) override;

		private:
			ctoot::audio::core::AudioBuffer* sharedBuffer{ nullptr };

		public:
			InterconnectionOutputProcess(ctoot::audio::core::AudioBuffer* sharedBuffer);
			~InterconnectionOutputProcess();
	
		};
	
	}
}
