#pragma once
#include <cstdint>
#include <string>
#include <service/ServiceVisitor.hpp>
#include <service/ServiceDescriptor.hpp>
#include <vector>
#include <map>
#include <stdio.h>

namespace ctoot {
	namespace service {
		class ServiceProvider
		{

		public:
			int providerId{};
			std::string providerName{};
			std::string version{};
			std::string description{};

		public:
			virtual int getProviderId();
			virtual std::string getProviderName();
			virtual std::string getVersion();
			virtual std::string getDescription();

		private:
			std::map<std::string, std::vector<ServiceDescriptor*>> services{};

		public:
			virtual std::vector<ServiceDescriptor*>* service(std::string typeIdName);
			virtual void add(ServiceDescriptor* d);
			virtual void add(std::string typeIdName, std::string name, std::string description, std::string version);

		public:
			virtual void accept(ServiceVisitor* v, std::string typeIdName);

		public:
			virtual void visit(ServiceVisitor* v, std::vector<ServiceDescriptor*> dit);

		public:
			std::string toString();

		public:
			ServiceProvider(int providerId, std::string providerName, std::string description, std::string version);
			ServiceProvider() {}
		};

	}
}
