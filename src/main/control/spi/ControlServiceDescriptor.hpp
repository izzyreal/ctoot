#pragma once
#include <service/ServiceDescriptor.hpp>

namespace ctoot {
	namespace control {
		namespace spi {

			class ControlServiceDescriptor
				: public service::ServiceDescriptor
			{

			private:
				int moduleId{};

			public:
				int getModuleId();

				ControlServiceDescriptor(const std::string& typeIdName, const int moduleId, const std::string& name, const std::string& description, const std::string& version);
			};
		}
	}
}
