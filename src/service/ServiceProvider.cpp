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
    printf("ServiceProvider adding %s to %s, %s\n", typeIdName.c_str(), this->getProviderName().c_str(), this->getDescription().c_str());
    printf("ServiceProvider services size %i\n\n", (int)services.size());
	if (services.find(typeIdName) == services.end()) {
        printf("service not yet found, adding it\n");
		services[typeIdName] = vector<ServiceDescriptor*>{};
        if (services.find(typeIdName) == services.end()) {
            printf("service still not found!\n");
        } else {
            printf("service is now found, services size: %i.\n", (int) services.size());
        }
	}
	return &services[typeIdName];
}

void ServiceProvider::add(ServiceDescriptor* d)
{
	MLOG("ServiceProvider trying to add: " + d->getDescription());
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

ServiceProvider::~ServiceProvider() {
	MLOG("Service provider destructor called for " + getProviderName() + " " + getDescription() + " id " + to_string(getProviderId()));
	for (auto& s : services) {
		for (auto& sd : s.second) {
			if (sd != nullptr) delete sd;
		}
	}
}
