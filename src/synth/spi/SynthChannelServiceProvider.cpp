#include <synth/spi/SynthChannelServiceProvider.hpp>

#include <control/spi/ControlServiceDescriptor.hpp>
#include <service/ServiceDescriptor.hpp>
#include <synth/SynthChannelControls.hpp>
#include <synth/spi/SynthChannelControlServiceDescriptor.hpp>

#include <boost/core/demangle.hpp>

using namespace ctoot::synth::spi;
using namespace ctoot::synth;

SynthChannelServiceProvider::SynthChannelServiceProvider(int32_t providerId, std::string providerName, std::string description, std::string version)
	: ctoot::service::ServiceProvider(providerId, providerName, description, version)
{
	std::string info = boost::core::demangle(typeid(SynthChannelControls).name());
	controls = service(info);
}

std::string ctoot::synth::spi::SynthChannelServiceProvider::lookupName(int32_t moduleId)
{
	for (auto& c : *controls) {
		try {
			auto d = dynamic_cast<control::spi::ControlServiceDescriptor*>(c);
			if (d->getModuleId() == moduleId) {
				return d->getChildClass();
			}
		}
		catch (const std::exception& e) {
		}
	}
	return {};
}

std::shared_ptr<ctoot::synth::SynthChannelControls> ctoot::synth::spi::SynthChannelServiceProvider::createControls(int32_t moduleId)
{
	for (auto& c : *controls) {
		try {
			auto d = dynamic_cast<control::spi::ControlServiceDescriptor*>(c);
			if (d->getModuleId() == moduleId) {
				auto candidate = std::dynamic_pointer_cast<SynthChannelControls>(ctoot::control::Control::create(d->getChildClass()));
				return candidate;
			}
		}
		catch (const std::exception& e) {
		}
	}
	return {};
}

void spi::SynthChannelServiceProvider::addControls(std::string typeIdName, int32_t moduleId, std::string name, std::string description, std::string version)
{
    add(new SynthChannelControlServiceDescriptor(typeIdName, moduleId, name, description, version));
}

std::shared_ptr<ctoot::synth::SynthChannelControls> ctoot::synth::spi::SynthChannelServiceProvider::createControls(std::string name)
{
	for (auto& c : *controls) {
		try {
			auto d = dynamic_cast<control::spi::ControlServiceDescriptor*>(c);
			if (d->getChildClass().compare(name) == 0) {
				auto candidate = std::dynamic_pointer_cast<SynthChannelControls>(ctoot::control::Control::create(d->getChildClass()));
				return candidate;
			}
		}
		catch (const std::exception& e) {
		}
	}
	return {};
}
