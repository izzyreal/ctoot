#pragma once
#include <service/ServiceProvider.hpp>

#include <memory>

namespace ctoot {
	namespace synth {

		class SynthControls;
		class MidiSynth;

		namespace spi {
			class SynthServiceProvider
				: public ctoot::service::ServiceProvider
			{

			private:
				std::vector<ctoot::service::ServiceDescriptor*>* controls{};

			public:
				virtual std::string lookupName(int32_t moduleId);
				virtual std::shared_ptr<ctoot::synth::SynthControls> createControls(int32_t moduleId);

			protected:
				virtual void addControls(std::string typeIdName, int32_t moduleId, std::string name, std::string description, std::string version);

			public:
				virtual std::shared_ptr<ctoot::synth::SynthControls> createControls(std::string name);

			protected:
				virtual std::shared_ptr<ctoot::synth::SynthControls> createControls(ctoot::service::ServiceDescriptor* d);

			public:
				virtual std::shared_ptr<ctoot::synth::MidiSynth> createSynth(ctoot::synth::SynthControls* controls) {
					return {};
				}

				SynthServiceProvider(int32_t providerId, std::string providerName, std::string description, std::string version);
				SynthServiceProvider() {}

			};

		}
	}
}
