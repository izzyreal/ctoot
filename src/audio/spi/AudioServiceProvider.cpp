#include <audio/spi/AudioServiceProvider.hpp>

#include <audio/core/AudioControls.hpp>
#include <audio/spi/AudioControlServiceDescriptor.hpp>
#include <control/spi/ControlServiceDescriptor.hpp>
#include <service/ServiceDescriptor.hpp>

using namespace ctoot::audio::spi;
using namespace ctoot::audio::core;
using namespace std;

AudioServiceProvider::AudioServiceProvider(int providerId, string providerName, string description, string version)
	: ServiceProvider(providerId, providerName, description, version)
{
	string info = typeid(AudioControls).name();
	controls = service(info);
}

string AudioServiceProvider::getAvailableControls() {
	string res;
	for (auto& c : *controls) {
		res += c->getChildClass() + "\n";
	}
	return res;
}

string AudioServiceProvider::lookupName(int moduleId)
{
	auto d = lookupDescriptor(moduleId);
	return d == nullptr ? static_cast<string>(nullptr) : d->getChildClass();
}

ctoot::service::ServiceDescriptor* AudioServiceProvider::lookupDescriptor(int moduleId)
{
	for (int i = 0; i < controls->size(); i++) {
		service::ServiceDescriptor* d = dynamic_cast<service::ServiceDescriptor*>((*controls)[i]);
		if (dynamic_cast<control::spi::ControlServiceDescriptor*>(d)->getModuleId() == moduleId) {
			return d;
		}
	}
	return nullptr;
}

void AudioServiceProvider::addControls(string typeIdName, int moduleId, string name, string description, string version)
{
	add(new AudioControlServiceDescriptor(typeIdName, moduleId, name, description, version));
}

void AudioServiceProvider::addControls(string typeIdName, int moduleId, string name, string description, string version, std::weak_ptr<ChannelFormat> format, string path)
{
	add(new AudioControlServiceDescriptor(typeIdName, moduleId, name, description, version, format, path));
}

shared_ptr<AudioControls> AudioServiceProvider::createControls(int moduleId)
{
	for (int i = 0; i < controls->size(); i++) {
		try {
			auto d = dynamic_cast<AudioControlServiceDescriptor::ControlServiceDescriptor*>((*controls)[i]);
			if (d->getModuleId() == moduleId) return createControls(d);
		}
		catch (const bad_cast &e) {
			string msg = e.what();
			MLOG("AudioServiceProvider::createControls bad cast, error msg " + msg);
		}
	}
	return {};
}

shared_ptr<AudioControls> AudioServiceProvider::createControls(string name)
{
	for (int i = 0; i < controls->size(); i++) {
		service::ServiceDescriptor* d = dynamic_cast<service::ServiceDescriptor*>((*controls)[i]);
		if (d->getChildClass().compare(name) == 0) {
			return createControls(d);
		}
	}
	return {};
}

shared_ptr<AudioControls> AudioServiceProvider::createControls(ctoot::service::ServiceDescriptor* d)
{
	auto candidate = dynamic_pointer_cast<AudioControls>(ctoot::control::Control::create(d->getChildClass()));
	if (candidate) {
		return candidate;
	}
	return {};
}
