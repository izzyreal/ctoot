#pragma once
#include <service/Services.hpp>
#include <audio/spi/AudioServiceProvider.hpp>
#include <audio/core/AudioControls.hpp>
#include <audio/core/AudioProcess.hpp>

#include <memory>

namespace ctoot {
	namespace audio {
		namespace core {

			class AudioServices
				: public service::Services
			{

			private:
				static std::vector<std::weak_ptr<ctoot::audio::spi::AudioServiceProvider>> providers;

			public:
				static void scan();

			public:
				static std::shared_ptr<AudioProcess> createProcess(std::weak_ptr<AudioControls> controls);
				static void accept(std::weak_ptr<service::ServiceVisitor> v, const std::string& typeIdName);

                static std::string getAvailableControls();

			protected:
				AudioServices();

			};
		}
	}
}
