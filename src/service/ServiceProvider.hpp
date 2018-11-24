#pragma once
#include <cstdint>
#include <string>
#include <service/ServiceVisitor.hpp>
#include <service/ServiceDescriptor.hpp>
#include <vector>
#include <memory>
#include <map>
#include <stdio.h>

namespace ctoot {
	namespace service {
		class ServiceProvider
		{

		public:
			int providerId;
			std::string providerName;
			std::string version;
			std::string description;

		public:
			virtual int getProviderId();
			virtual std::string getProviderName();
			virtual std::string getVersion();
			virtual std::string getDescription();

		private:
			std::map<std::string, std::shared_ptr<std::vector<std::shared_ptr<ServiceDescriptor>>>> services;

		public:
			virtual std::weak_ptr<std::vector<std::shared_ptr<ServiceDescriptor>>> service(const std::string& typeIdName);
			virtual void add(std::shared_ptr<ServiceDescriptor> d);
			virtual void add
			(
				const std::string& typeIdName, 
				const std::string& name,
				const std::string& description,
				const std::string& version
			);

		public:
			virtual void accept(std::weak_ptr<ServiceVisitor> v, const std::string& typeIdName);

		public:
			virtual void visit(std::weak_ptr<ServiceVisitor> v, const std::vector<std::shared_ptr<ServiceDescriptor>>& serviceDescriptors);

		public:
			std::string toString();

		public:
			ServiceProvider
			(
				int providerId, 
				const std::string& providerName, 
				const std::string& description, 
				const std::string& version
			);
			ServiceProvider() { providerName = "ServiceProvider dummy"; }
			~ServiceProvider();
		};

	}
}
