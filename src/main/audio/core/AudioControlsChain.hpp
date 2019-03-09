#pragma once
#include <control/CompoundControlChain.hpp>
#include <audio/core/ChannelFormat.hpp>
#include <audio/core/MetaInfo.hpp>

#include <vector>

namespace ctoot {

	namespace service {
		class ServiceDescriptor;
	}

	namespace audio {
		namespace core {

			class AudioControlsChain
				: public ctoot::control::CompoundControlChain
			{

			private:
				std::string sourceLabel{ "" };
				std::string sourceLocation{ "" };
				std::weak_ptr<ChannelFormat> constraintChannelFormat;

			public:
				virtual void setMetaInfo(std::weak_ptr<MetaInfo> metaInfo);
				virtual std::string getSourceLabel();
				virtual std::string getSourceLocation();

			public:
				std::shared_ptr<ctoot::control::CompoundControl> createControl(std::string name) override;
				int getMaxInstance() override;

			public:
				std::weak_ptr<ChannelFormat> getConstraintChannelFormat();
				bool isCompatibleDescriptor(ctoot::service::ServiceDescriptor* d);

			public:
				//std::vector<ctoot::service::ServiceDescriptor*> descriptors() override;
				std::string getPersistenceDomain() override;

			public:
				AudioControlsChain(int id, std::string name);
				AudioControlsChain(int id, int index, std::string name, std::weak_ptr<ChannelFormat> constraintFormat);
				virtual ~AudioControlsChain();

			};

		}
	}
}
