#include <synth/spi/SynthChannelServiceProvider.hpp>

#include <control/spi/ControlServiceDescriptor.hpp>
#include <service/ServiceDescriptor.hpp>
#include <synth/SynthChannelControls.hpp>
#include <synth/spi/SynthChannelControlServiceDescriptor.hpp>

#include <boost/core/demangle.hpp>

using namespace ctoot::synth::spi;
using namespace ctoot::synth;
using namespace ctoot::control::spi;
using namespace std;

SynthChannelServiceProvider::SynthChannelServiceProvider
(
	int32_t providerId, 
	const string& providerName, 
	const string& description, 
	const string& version
)
	: ctoot::service::ServiceProvider(providerId, providerName, description, version)
{
	string info = boost::core::demangle(typeid(SynthChannelControls).name());
	controls = service(info);
}

string SynthChannelServiceProvider::lookupName(int32_t moduleId)
{
	for (auto& c : *controls.lock()) {
		auto d = dynamic_pointer_cast<ControlServiceDescriptor>(c);
		if (d && d->getModuleId() == moduleId) {
			return d->getChildClass();
		}
	}
	return {};
}

shared_ptr<ctoot::synth::SynthChannelControls> SynthChannelServiceProvider::createControls(int32_t moduleId)
{
	for (auto& c : *controls.lock()) {
		auto d = dynamic_pointer_cast<control::spi::ControlServiceDescriptor>(c);
		if (d->getModuleId() == moduleId) {
			auto candidate = dynamic_pointer_cast<SynthChannelControls>(ctoot::control::Control::create(d->getChildClass()));
			if (candidate) return candidate;
		}
	}
	return {};
}

void SynthChannelServiceProvider::addControls
(
	const string& typeIdName, 
	int32_t moduleId, 
	const string& name, 
	const string& description, 
	const string& version
)
{
    add(make_shared<SynthChannelControlServiceDescriptor>(typeIdName, moduleId, name, description, version));
}

shared_ptr<ctoot::synth::SynthChannelControls> SynthChannelServiceProvider::createControls(const string& name)
{
	for (auto& c : *controls.lock()) {
		auto d = dynamic_pointer_cast<control::spi::ControlServiceDescriptor>(c);
		if (d && d->getChildClass().compare(name) == 0) {
			auto candidate = dynamic_pointer_cast<SynthChannelControls>(ctoot::control::Control::create(d->getChildClass()));
			if (candidate) return candidate;
		}
	}
	return {};
}
