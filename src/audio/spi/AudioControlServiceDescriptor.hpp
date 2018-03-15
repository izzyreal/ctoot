#pragma once
#include <control/spi/ControlServiceDescriptor.hpp>
#include <audio/core/ChannelFormat.hpp>

#include <memory>

namespace ctoot {
	namespace audio {
		namespace spi {

			class AudioControlServiceDescriptor
				: public control::spi::ControlServiceDescriptor
			{

			private:
                std::weak_ptr<ctoot::audio::core::ChannelFormat> channelFormat;
				std::string pluginPath;

			public:
				virtual std::weak_ptr<ctoot::audio::core::ChannelFormat> getChannelFormat();
				virtual std::string getPluginPath();

			public:
				AudioControlServiceDescriptor(std::string typeIdName, int moduleId, std::string name, std::string description, std::string version);
				AudioControlServiceDescriptor(std::string typeIdName, int moduleId, std::string name, std::string description, std::string version, std::weak_ptr<ctoot::audio::core::ChannelFormat> format, std::string path);
			};

		}
	}
}
