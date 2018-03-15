#include <service/ServiceProvider.hpp>
#include <service/ServiceVisitor.hpp>

#include <iterator>
#include <stdio.h>
#include <iostream>

#include <Logger.hpp>

using namespace ctoot::service;
using namespace std;

ServiceProvider::ServiceProvider(int providerId, string providerName, string description, string version)
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

vector<ServiceDescriptor*>* ServiceProvider::service(string typeIdName)
{
	if (services.find(typeIdName) == services.end()) {
		services[typeIdName] = vector<ServiceDescriptor*>{};
	}
	return &services[typeIdName];
}

void ServiceProvider::add(ServiceDescriptor* d)
{
	auto candidate = services.find(d->getParentClass());
	if (candidate != services.end()) {
		services[d->getParentClass()].push_back(d);
	}
}

void ServiceProvider::add(string typeIdName, string name, string description, string version)
{
	ServiceDescriptor* toAdd = new ServiceDescriptor(typeIdName, name, description, version);
    add(toAdd);
}


void ServiceProvider::accept(ServiceVisitor* v, string typeIdName)
{
	v->visitProvider(this);
	if (typeIdName.compare("") == 0) {
		for (map<string, vector<ServiceDescriptor*>>::iterator it = services.begin(); it != services.end(); ++it) {
			vector<ServiceDescriptor*> vectorToVisit = it->second;
			visit(v, vectorToVisit);
		}
	}
	else {
		visit(v, services[typeIdName]);
	}
}


void ServiceProvider::visit(ServiceVisitor* v, vector<ServiceDescriptor*> dit)
{
	for (auto& sd : dit) {
		v->visitDescriptor(sd);
	}
}

string ServiceProvider::toString()
{
	return string(" v" + version + " by " + providerName);
}
