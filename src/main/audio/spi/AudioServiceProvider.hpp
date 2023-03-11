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
				std::weak_ptr<std::vector<std::shared_ptr<ctoot::service::ServiceDescriptor>>> controls;

			public:
                virtual std::weak_ptr<service::ServiceDescriptor> lookupDescriptor(int moduleId);

			public:
				virtual void addControls
				(
					const std::string& typeIdName, 
					int moduleId, 
					const std::string& name,
					const std::string& description,
					const std::string& version
				);

            public:
				virtual std::shared_ptr<ctoot::audio::core::AudioControls> createControls(int moduleId);
				virtual std::shared_ptr<ctoot::audio::core::AudioControls> createControls(const std::string& name);
				virtual std::shared_ptr<ctoot::audio::core::AudioControls> createControls(std::weak_ptr<service::ServiceDescriptor> d);
				virtual std::shared_ptr<ctoot::audio::core::AudioProcess> createProcessor(std::weak_ptr<audio::core::AudioControls> c) { return {}; };

			public:
				std::string getAvailableControls();

			public:
				AudioServiceProvider
				(
					int providerId, 
					const std::string& providerName,
					const std::string& description,
					const std::string& version
				);
				
				AudioServiceProvider(const std::string& providerName) { this->providerName = providerName; }
			};
		}
	}
}
