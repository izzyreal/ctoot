#include <audio/spi/AudioServiceProvider.hpp>

#include <audio/core/AudioControls.hpp>
#include <audio/spi/AudioControlServiceDescriptor.hpp>

using namespace ctoot::audio::spi;
using namespace ctoot::audio::core;
using namespace std;

#include <System.hpp>

AudioServiceProvider::AudioServiceProvider
(
	int providerId, 
	const string& providerName, 
	const string& description,
	const string& version
)
	: ServiceProvider(providerId, providerName, description, version)
{
    string info = moduru::System::demangle(typeid(AudioControls).name());
	//MLOG("setting controls for " + description);
	//MLOG("info (typeid name) " + info);
	controls = service(info);
    //MLOG("controls size is now " + to_string(controls.lock()->size()));
}

string AudioServiceProvider::getAvailableControls() {
	string res;
	for (auto& c : *controls.lock()) {
		res += c->getChildClass() + "\n";
	}
	return res;
}

weak_ptr<ctoot::service::ServiceDescriptor> AudioServiceProvider::lookupDescriptor(int moduleId)
{
	auto c = controls.lock();
	for (int i = 0; i < c->size(); i++) {
		auto d = c->at(i);
		if (dynamic_pointer_cast<control::spi::ControlServiceDescriptor>(d)->getModuleId() == moduleId) {
			return d;
		}
	}
	return {};
}

void AudioServiceProvider::addControls
(
	const string& typeIdName, 
	int moduleId, 
	const string& name,
	const string& description,
	const string& version
)
{
	auto descriptor = make_shared<AudioControlServiceDescriptor>(typeIdName, moduleId, name, description, version);
	add(descriptor);
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
    //MLOG("AudioServiceProvider::createControls name " + name);
    //MLOG("AudioServiceProvider::createControls controls size " + to_string(controls.lock()->size()));
    
	auto c = controls.lock();
	for (int i = 0; i < c->size(); i++) {
		auto d = c->at(i);
        //MLOG("AudioServiceProvider::createControls control descriptor child class " + d->getChildClass());
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
