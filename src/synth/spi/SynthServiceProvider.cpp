#include <synth/spi/SynthServiceProvider.hpp>

#include <control/spi/ControlServiceDescriptor.hpp>
#include <service/ServiceDescriptor.hpp>
#include <synth/SynthControls.hpp>
#include <synth/spi/SynthControlServiceDescriptor.hpp>

using namespace ctoot::synth::spi;

SynthServiceProvider::SynthServiceProvider(int32_t providerId, std::string providerName, std::string description, std::string version)
	: ctoot::service::ServiceProvider(providerId, providerName, description, version)
{
	std::string info = typeid(SynthControls).name();
	controls = service(info);
}

std::string SynthServiceProvider::lookupName(int32_t moduleId)
{
	for (auto& c : *controls) {
		auto d = dynamic_cast<control::spi::ControlServiceDescriptor*>(c);
		try {
			if (d->getModuleId() == moduleId) {
				return d->getChildClass();
			}
		}
		catch (const std::exception& e) {
		}
	}
	return {};
}

 std::shared_ptr<ctoot::synth::SynthControls> SynthServiceProvider::createControls(int32_t moduleId)
{
	 for (auto& c : *controls) {
		 auto d = dynamic_cast<control::spi::ControlServiceDescriptor*>(c);
		 try {
			 if (d->getModuleId() == moduleId) {
				 return createControls(d);
            }
		 }
		 catch (const std::exception& e) {
		 }
	 }
	 return {};
}

void spi::SynthServiceProvider::addControls(std::string typeIdName, int32_t moduleId, std::string name, std::string description, std::string version)
{
    add(new SynthControlServiceDescriptor(typeIdName, moduleId, name, description, version));
}

std::shared_ptr<ctoot::synth::SynthControls> SynthServiceProvider::createControls(std::string name)
{
	for (auto& c : *controls) {
		auto d = dynamic_cast<control::spi::ControlServiceDescriptor*>(c);
		try {
			if (d->getChildClass().compare(name) == 0) {
				return createControls(d);
			}
		}
		catch (const std::exception& e) {
		}
	}
	return {};
}

 std::shared_ptr<ctoot::synth::SynthControls> SynthServiceProvider::createControls(ctoot::service::ServiceDescriptor* d)
{
	 try {
		 auto candidate = std::dynamic_pointer_cast<SynthControls>(ctoot::control::Control::create(d->getChildClass()));
		 return candidate;
	 }
	 catch (const std::exception& e) {
	 }
	 return {};
}
