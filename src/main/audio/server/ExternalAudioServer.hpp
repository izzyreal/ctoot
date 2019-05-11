/**
* The ExternalAudioServer expects someone else to talk to the host OS audio API's.
* 
* After instantiating an ExternalAudioServer and starting it, we can make it work(),
* optionally providing it with input and output buffers. After calling work, the input data
* has been processed and consumed by ctoot, and ctoot will have filled the output data with
* AudioMixer's main output data.
**/

#pragma once
#include <audio/server/AudioServer.hpp>

//#include <RtAudio.h>

#include <string>
#include <vector>
#include <memory>
#include <thread>
#include <mutex>

namespace ctoot {
	namespace audio {
		namespace server {

			class ExternalAudioServer
				: public AudioServer {

			public:
				void start() override;
				void stop() override;
				bool isRunning() override;
				void close() override;
				void setClient(std::weak_ptr<AudioClient> client) override;
				std::vector<std::string> getAvailableOutputNames() override;
				std::vector<std::string> getAvailableInputNames() override;
				IOAudioProcess* openAudioOutput(std::string name, std::string label) override;
				IOAudioProcess* openAudioInput(std::string name, std::string glabel) override;
				void closeAudioOutput(ctoot::audio::server::IOAudioProcess* output) override;
				void closeAudioInput(ctoot::audio::server::IOAudioProcess* input) override;
				float getLoad() override;
				int getInputLatencyFrames() override;
				int getOutputLatencyFrames() override;
				int getTotalLatencyFrames() override;

			public:
				void work() override;
				void work(float* inputBuffer, float* outputBuffer, int nFrames, int inputChannelCount, int outputChannelCount);

			public:
				ExternalAudioServer();

			};
		}
	}
}
