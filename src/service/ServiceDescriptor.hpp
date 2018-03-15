#pragma once
#include <string>
#include <typeinfo>

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
			virtual std::string getParentClass();
			virtual std::string getChildClass();
			virtual std::string getDescription();
			virtual std::string getVersion();
			std::string toString();

		public:
			ServiceDescriptor(std::string typeIdName, std::string name, std::string description, std::string version);

		};
	}
}
