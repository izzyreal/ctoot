#pragma once
#include <service/ServiceProvider.hpp>
#include <audio/core/ChannelFormat.hpp>
#include <audio/core/AudioControls.hpp>
#include <audio/core/AudioProcess.hpp>

#include <memory>

namespace ctoot {
	namespace audio {
		namespace spi {

			class AudioServiceProvider
				: public ctoot::service::ServiceProvider
			{

			private:
				std::vector<ctoot::service::ServiceDescriptor*>* controls{};

			public:
				virtual std::string lookupName(int moduleId);
				virtual service::ServiceDescriptor* lookupDescriptor(int moduleId);

			public:
				virtual void addControls(std::string typeIdName, int moduleId, std::string name, std::string description, std::string version);
				virtual void addControls(std::string typeIdName, int moduleId, std::string name, std::string description, std::string version, std::weak_ptr<ctoot::audio::core::ChannelFormat> format, std::string path);

			public:
				virtual std::shared_ptr<ctoot::audio::core::AudioControls> createControls(int moduleId);
				virtual std::shared_ptr<ctoot::audio::core::AudioControls> createControls(std::string name);
				virtual std::shared_ptr<ctoot::audio::core::AudioControls> createControls(service::ServiceDescriptor* d);
				virtual std::shared_ptr<ctoot::audio::core::AudioProcess> createProcessor(std::weak_ptr<audio::core::AudioControls> c) { return {}; };

			public:
				std::string getAvailableControls();

			public:
				AudioServiceProvider(int providerId, std::string providerName, std::string description, std::string version);
				AudioServiceProvider() {}
			};
		}
	}
}
