#pragma once
#include <audio/server/IOAudioProcess.hpp>

#include <string>

namespace ctoot {
	namespace audio {

		namespace core {
			class ChannelFormat;
		}

		namespace server {

			class AudioServerProcess
				: public IOAudioProcess
			
			{

			private:
				std::string name{ "" };
			
			protected:
				std::weak_ptr<ctoot::audio::core::ChannelFormat> format;

			public:
				std::string getName() override;
				std::weak_ptr<ctoot::audio::core::ChannelFormat> getChannelFormat() override;

				virtual void open() override = 0;
				virtual void close() override = 0;

				AudioServerProcess(std::string name, bool mono);
			};

		}
	}
}
