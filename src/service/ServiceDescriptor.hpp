#pragma once
#include <string>

namespace ctoot {
	namespace service {

		class ServiceDescriptor
		{

		private:
			std::string parentClass;
			std::string childClass;
			std::string description;
			std::string version;

		public:
			std::string getParentClass();
			std::string getChildClass();
			std::string getDescription();
			std::string getVersion();
			std::string toString();

		public:
			ServiceDescriptor(const std::string& parentClass, const std::string& childClass, const std::string& description, const std::string& version);
			virtual ~ServiceDescriptor() {}
		};
	}
}
