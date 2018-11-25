#include <synth/spi/SynthServiceProvider.hpp>

#include <control/spi/ControlServiceDescriptor.hpp>
#include <service/ServiceDescriptor.hpp>
#include <synth/SynthControls.hpp>
#include <synth/spi/SynthControlServiceDescriptor.hpp>

#include <boost/core/demangle.hpp>

using namespace ctoot::synth::spi;
using namespace std;

SynthServiceProvider::SynthServiceProvider
(
	int32_t providerId, 
	const string& providerName, 
	const string& description, 
	const string& version
)
	: ctoot::service::ServiceProvider(providerId, providerName, description, version)
{
	string info = boost::core::demangle(typeid(SynthControls).name());
	controls = service(info);
}

string SynthServiceProvider::lookupName(int32_t moduleId)
{
	for (auto& c : *controls.lock()) {
		auto d = dynamic_pointer_cast<ctoot::control::spi::ControlServiceDescriptor>(c);
		if (d && d->getModuleId() == moduleId) {
			return d->getChildClass();
		}
	}
	return {};
}

shared_ptr<ctoot::synth::SynthControls> SynthServiceProvider::createControls(int32_t moduleId)
{
	for (auto& c : *controls.lock()) {
		auto d = dynamic_pointer_cast<control::spi::ControlServiceDescriptor>(c);
		if (d->getModuleId() == moduleId) {
			return createControls(d);
		}
		return {};
	}
}

void SynthServiceProvider::addControls
(
	const string& typeIdName, 
	int32_t moduleId, 
	const string& name, 
	const string& description, 
	const string& version
)
{
    add(make_shared<SynthControlServiceDescriptor>(typeIdName, moduleId, name, description, version));
}

shared_ptr<ctoot::synth::SynthControls> SynthServiceProvider::createControls(const string& name)
{
	for (auto& c : *controls.lock()) {
		auto d = dynamic_pointer_cast<control::spi::ControlServiceDescriptor>(c);
		if (d && d->getChildClass().compare(name) == 0) {
			return createControls(d);
		}
	}
	return {};
}

shared_ptr<ctoot::synth::SynthControls> SynthServiceProvider::createControls(weak_ptr<ctoot::service::ServiceDescriptor> d)
{
	auto candidate = dynamic_pointer_cast<SynthControls>(ctoot::control::Control::create(d.lock()->getChildClass()));
	if (candidate) return candidate;
	return {};
}
