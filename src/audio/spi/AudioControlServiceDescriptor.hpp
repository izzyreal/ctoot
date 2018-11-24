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
				AudioControlServiceDescriptor(
					const std::string& typeIdName, 
					int moduleId, 
					const std::string& name, 
					const std::string& description, 
					const std::string& version);

				AudioControlServiceDescriptor(const std::string& typeIdName, 
					int moduleId, 
					const std::string& name,
					const std::string& description,
					const std::string& version,
					std::weak_ptr<ctoot::audio::core::ChannelFormat> format, 
					const std::string& path);
			};

		}
	}
}
