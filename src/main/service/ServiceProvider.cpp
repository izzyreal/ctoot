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
	const string& providerName,
	const string& description, 
	const string& version
)
{
	services.clear();
	this->providerName = providerName;
	this->description = description;
	this->version = version;
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
 	if (services.find(typeIdName) == services.end()) {
 		services[typeIdName] = make_shared<vector<shared_ptr<ServiceDescriptor>>>();
 	}
	return services[typeIdName];
}

void ServiceProvider::add(shared_ptr<ServiceDescriptor> d)
{
	auto candidate = services.find(d->getParentClass());
	if (candidate != services.end()) {
		services[d->getParentClass()]->push_back(std::move(d));
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