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

			private:
				std::vector<ctoot::service::ServiceDescriptor*>* controls{};

			public:
				virtual std::string lookupName(int32_t moduleId);
				virtual std::shared_ptr<ctoot::synth::SynthChannelControls> createControls(int32_t moduleId);

			protected:
				virtual void addControls(std::string typeIdName, int32_t moduleId, std::string name, std::string description, std::string version);

			public:
				virtual std::shared_ptr<ctoot::synth::SynthChannelControls> createControls(std::string name);
				virtual std::shared_ptr<ctoot::synth::SynthChannel> createSynthChannel(std::weak_ptr<ctoot::synth::SynthChannelControls> controls2) {
					return {};
				}

				SynthChannelServiceProvider(int32_t providerId, std::string providerName, std::string description, std::string version);
				SynthChannelServiceProvider() {}

			};

		}
	}
}
