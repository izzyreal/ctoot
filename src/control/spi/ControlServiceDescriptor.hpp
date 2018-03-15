#pragma once
#include <service/ServiceDescriptor.hpp>
#include <cstdint>

namespace ctoot {
	namespace control {
		namespace spi {

			class ControlServiceDescriptor
				: public service::ServiceDescriptor
			{

			private:
				int moduleId{};

			public:
				virtual int getModuleId();

				ControlServiceDescriptor(std::string typeIdName, int moduleId, std::string name, std::string description, std::string version);
			};
		}
	}
}
