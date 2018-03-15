#include <control/spi/ControlServiceDescriptor.hpp>

using namespace ctoot::control::spi;
using namespace std;

ControlServiceDescriptor::ControlServiceDescriptor(string typeIdName, int moduleId, string name, string description, string version)
	: ServiceDescriptor(typeIdName, name, description, version)
{
	this->moduleId = moduleId;
}

int ControlServiceDescriptor::getModuleId()
{
    return moduleId;
}
