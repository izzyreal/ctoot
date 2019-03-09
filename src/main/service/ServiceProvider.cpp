#include <service/ServiceProvider.hpp>
#include <service/ServiceVisitor.hpp>

#include <iterator>
#include <stdio.h>
#include <iostream>

#include <Logger.hpp>

using namespace ctoot::service;
using namespace std;

ServiceProvider::ServiceProvider
(
	int providerId, 
	const string& providerName, 
	const string& description, 
	const string& version
)
{
	services.clear();
	this->providerId = providerId;
	this->providerName = providerName;
	this->description = description;
	this->version = version;
}

int ServiceProvider::getProviderId()
{
    return providerId;
}

string ServiceProvider::getProviderName()
{
    return providerName;
}

string ServiceProvider::getVersion()
{
    return version;
}

string ServiceProvider::getDescription()
{
    return description;
}

weak_ptr<vector<shared_ptr<ServiceDescriptor>>> ServiceProvider::service(const string& typeIdName)
{
    MLOG("\nServiceProvider adding " + typeIdName + " to " + this->getProviderName() + ", " + this->getDescription());
    MLOG("ServiceProvider services size " + to_string(services.size()));
	if (services.find(typeIdName) == services.end()) {
        MLOG("service not yet found, adding it");
		services[typeIdName] = make_shared<vector<shared_ptr<ServiceDescriptor>>>();
        if (services.find(typeIdName) == services.end()) {
            MLOG("service still not found!");
        } else {
            MLOG("service is now found, services size: " + to_string(services.size()));
        }
	}
	return services[typeIdName];
}

void ServiceProvider::add(shared_ptr<ServiceDescriptor> d)
{
	MLOG("ServiceProvider trying to add: " + d->getDescription());
	auto candidate = services.find(d->getParentClass());
	if (candidate != services.end()) {
		MLOG("ServiceProvider added: " + d->getDescription());
		MLOG("services vector size is now " + to_string(services[d->getParentClass()]->size()));
		services[d->getParentClass()]->push_back(std::move(d));
	}
	else {
		MLOG("!!ServiceProvider not added!! " + d->getDescription());
	}
}

void ServiceProvider::add
(
	const string& typeIdName, 
	const string& name,
	const string& description,
	const string& version
)
{
	auto toAdd = make_shared<ServiceDescriptor>(typeIdName, name, description, version);
    add(toAdd);
}


void ServiceProvider::accept(weak_ptr<ServiceVisitor> v, const string& typeIdName)
{
	v.lock()->visitProvider(this);
	if (typeIdName.compare("") == 0) {
		for (auto it = services.begin(); it != services.end(); ++it) {
			auto vectorToVisit = it->second;
			//visit(v, vectorToVisit);
		}
	}
	else {
		//visit(v, services[typeIdName]);
	}
}


void ServiceProvider::visit(weak_ptr<ServiceVisitor> v, const vector<shared_ptr<ServiceDescriptor>>& serviceDescriptors)
{
	for (auto& sd : serviceDescriptors)
		v.lock()->visitDescriptor(sd.get());
}

string ServiceProvider::toString()
{
	return string(" v" + version + " by " + providerName);
}

ServiceProvider::~ServiceProvider() {
}
