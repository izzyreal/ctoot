#include <control/spi/ControlServiceDescriptor.hpp>

using namespace ctoot::control::spi;
using namespace std;

ControlServiceDescriptor::ControlServiceDescriptor(const string& typeIdName, int moduleId, const string& name, const string& description, const string& version)
	: ServiceDescriptor(typeIdName, name, description, version)
{
	this->moduleId = moduleId;
}

int ControlServiceDescriptor::getModuleId()
{
    return moduleId;
}
