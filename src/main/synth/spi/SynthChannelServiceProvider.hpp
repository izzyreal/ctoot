#pragma once

#include <service/ServiceProvider.hpp>

#include <memory>

namespace ctoot {
	namespace synth {

		class SynthChannelControls;
		class SynthChannel;

		namespace spi {

			class SynthChannelServiceProvider
				: public ctoot::service::ServiceProvider
			{

            public:
                SynthChannelServiceProvider
                (
                 int32_t providerId,
                 const std::string& providerName,
                 const std::string& description,
                 const std::string& version
                 );
                virtual ~SynthChannelServiceProvider() {}
                
                SynthChannelServiceProvider() { providerName = "SynthChannelServiceProvider dummy"; }
                
			private:
				std::weak_ptr<std::vector<std::shared_ptr<ctoot::service::ServiceDescriptor>>> controls;

			public:
                virtual std::shared_ptr<ctoot::synth::SynthChannelControls> createControls(int32_t moduleId);

			protected:
				void addControls
				(
					const std::string& typeIdName, 
					int32_t moduleId, 
					const std::string& name, 
					const std::string& description,
					const std::string& version
				);

			public:
				virtual std::shared_ptr<ctoot::synth::SynthChannelControls> createControls(const std::string& name);
				virtual std::shared_ptr<ctoot::synth::SynthChannel> createSynthChannel(std::weak_ptr<ctoot::synth::SynthChannelControls> controls) {
					return {};
				}
                
			};

		}
	}
}
