#pragma once

#include <service/Services.hpp>

#include <synth/spi/SynthServiceProvider.hpp>

namespace ctoot {
	namespace synth {
		class SynthServices
			: public ctoot::service::Services
		{

		private:
			static std::vector<std::weak_ptr<ctoot::synth::spi::SynthServiceProvider>> providers;

		public:
			static std::string lookupModuleName(int32_t providerId, int32_t moduleId);
			static std::shared_ptr<SynthControls> createControls(std::string name);
			static std::shared_ptr<MidiSynth> createSynth(std::weak_ptr<SynthControls> controls);
			static void scan();
			static void accept(service::ServiceVisitor* v, std::string typeIdName);
			static void printServiceDescriptors(std::string typeIdName);

		protected:
			SynthServices();

		};

	}
}
