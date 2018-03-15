#pragma once
#include <audio/core/AudioControlsChain.hpp>
#include <service/ServiceVisitor.hpp>
#include <service/ServiceDescriptor.hpp>
#include <vector>

using namespace ctoot::service;

namespace ctoot {
	namespace audio {
		namespace core {

			class Descriptors
				: public ServiceVisitor
			{

			public:
				void visitDescriptor(ServiceDescriptor* d) override;

				Descriptors(AudioControlsChain *AudioControlsChain_this, std::vector<ServiceDescriptor>* descriptors);
				AudioControlsChain *AudioControlsChain_this;
				std::vector<ServiceDescriptor*> descriptors;

			private:
				friend class AudioControlsChain;

			};
		}
	}
}
