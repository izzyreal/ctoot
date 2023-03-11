#include <audio/spi/AudioServiceProvider.hpp>

#include <audio/core/AudioControls.hpp>
#include <audio/spi/AudioControlServiceDescriptor.hpp>

using namespace ctoot::audio::spi;
using namespace ctoot::audio::core;
using namespace std;

#include <System.hpp>

AudioServiceProvider::AudioServiceProvider
(
	const string& providerName,
	const string& description,
	const string& version
)
	: ServiceProvider(providerName, description, version)
{
    string info = moduru::System::demangle(typeid(AudioControls).name());
	controls = service(info);
}

string AudioServiceProvider::getAvailableControls() {
	string res;
	for (auto& c : *controls.lock()) {
		res += c->getChildClass() + "\n";
	}
	return res;
}

shared_ptr<AudioControls> AudioServiceProvider::createControls(int moduleId)
{
	auto c = controls.lock();
	for (int i = 0; i < c->size(); i++) {
		auto d = dynamic_pointer_cast<AudioControlServiceDescriptor::ControlServiceDescriptor>(c->at(i));
		if (d&& d->getModuleId() == moduleId) return createControls(d);
	}
	return {};
}

shared_ptr<AudioControls> AudioServiceProvider::createControls(const string& name)
{
	auto c = controls.lock();
	for (int i = 0; i < c->size(); i++) {
		auto d = c->at(i);

		if (d->getChildClass().compare(name) == 0) {
			return createControls(d);
		}
	}
	return {};
}

shared_ptr<AudioControls> AudioServiceProvider::createControls(weak_ptr<ctoot::service::ServiceDescriptor> d)
{
	auto c = ctoot::control::Control::create(d.lock()->getChildClass());
	auto ac = dynamic_pointer_cast<ctoot::audio::core::AudioControls>(c);
	if (ac) return ac;
	return {};
}
