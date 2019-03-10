#include <service/ServiceDescriptor.hpp>

#include <Logger.hpp>

using namespace ctoot::service;
using namespace std;

ServiceDescriptor::ServiceDescriptor(const string& parentClass, const string& childClass, const string& description, const string& version)
{
	this->parentClass = parentClass;
	this->childClass = childClass;
	this->description = description;
	this->version = version;
    
    //printf("\nServiceDescriptor constructor %s, %s", parentClass.c_str(), childClass.c_str());
    
	/*
	MLOG("\nServiceDescriptor parentClass: " + parentClass);
	MLOG("ServiceDescriptor childClass: " + childClass);
	MLOG("ServiceDescriptor description: " + description);
	MLOG("ServiceDescriptor version: " + version);
	*/
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
