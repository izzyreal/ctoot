#include <service/ServiceDescriptor.hpp>

#include <Logger.hpp>

using namespace ctoot::service;
using namespace std;

ServiceDescriptor::ServiceDescriptor(string parentClass, string childClass, string description, string version) 
{
	this->parentClass = parentClass;
	this->childClass = childClass;
	this->description = description;
	this->version = version;
	MLOG("\nServiceDescriptor parentClass: " + parentClass);
	MLOG("ServiceDescriptor childClass: " + childClass);
	MLOG("ServiceDescriptor description: " + description);
	MLOG("ServiceDescriptor version: " + version);
}

string ServiceDescriptor::getParentClass()
{
    return parentClass;
}

string ServiceDescriptor::getChildClass()
{
    return childClass;
}

string ServiceDescriptor::getDescription()
{
    return description;
}

string ServiceDescriptor::getVersion()
{
    return version;
}

string ServiceDescriptor::toString()
{
	return childClass + " " + version + " " + description + " " + parentClass;
}
