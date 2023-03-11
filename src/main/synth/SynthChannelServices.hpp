#pragma once

#include <service/Services.hpp>

#include <synth/spi/SynthChannelServiceProvider.hpp>

#include <memory>

namespace ctoot {
	namespace synth {
		class SynthChannelServices
			: public ctoot::service::Services
		{

		private:
			static std::vector<std::weak_ptr<ctoot::synth::spi::SynthChannelServiceProvider>> providers;

		public:
            static std::shared_ptr<SynthChannelControls> createControls(const std::string& name);
			static std::shared_ptr<SynthChannel> createSynthChannel(std::weak_ptr<SynthChannelControls> controls);
			static void scan();
			static void accept(std::weak_ptr<service::ServiceVisitor> v, const std::string& typeIdName);

        protected:
			SynthChannelServices();

		};
	}
}
