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
				std::weak_ptr<std::vector<std::shared_ptr<ctoot::service::ServiceDescriptor>>> controls;

			public:
                virtual std::shared_ptr<ctoot::synth::SynthControls> createControls(int32_t moduleId);

			protected:
				virtual void addControls
				(
					const std::string& typeIdName, 
					int32_t moduleId, 
					const std::string& typeIdNamename, 
					const std::string& typeIdNamedescription, 
					const std::string& typeIdNameversion
				);

			public:
				virtual std::shared_ptr<ctoot::synth::SynthControls> createControls(const std::string& name);

			protected:
				virtual std::shared_ptr<ctoot::synth::SynthControls> createControls(std::weak_ptr<ctoot::service::ServiceDescriptor> d);

			public:
				virtual std::shared_ptr<ctoot::synth::MidiSynth> createSynth(std::weak_ptr<ctoot::synth::SynthControls> controls) {
					return {};
				}

				SynthServiceProvider
				(
					int32_t providerId, 
					const std::string& providerName, 
					const std::string& description, 
					const std::string& version
				);
				
				SynthServiceProvider() { providerName = "SynthServiceProvider dummy"; }

			};

		}
	}
}
