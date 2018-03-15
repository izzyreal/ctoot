#include "AudioServices.hpp"

#include <audio/core/AudioControls.hpp>
#include <audio/core/AudioProcess.hpp>
#include <audio/spi/AudioServiceProvider.hpp>
//#include <service/ServicePrinter.hpp>
#include <service/ServiceProvider.hpp>

using namespace ctoot::audio::core;
using namespace std;

AudioServices::AudioServices()
	: ctoot::service::Services()
{
}

vector<weak_ptr<ctoot::audio::spi::AudioServiceProvider>> AudioServices::providers;

string AudioServices::lookupModuleName(int providerId, int moduleId)
{
	for (auto& p : providers) {
		if (p.lock()->getProviderId() == providerId) {
			return p.lock()->lookupName(moduleId);
		}
	}
	return "Module not found!";
}

shared_ptr<AudioControls> AudioServices::createControls(int providerId, int moduleId, int instanceIndex)
{
	shared_ptr<AudioControls> controls;
	for (auto& p : providers) {
		{
			if (p.lock()->getProviderId() == providerId) {
				controls = p.lock()->createControls(moduleId);
				if (controls) {
					controls->setProviderId(providerId);
					if (instanceIndex > 0) {
						controls->setName(controls->getName() + " #" + to_string(instanceIndex + 1));
						controls->setInstanceIndex(instanceIndex);
					}
					return controls;
				}
			}
		}
	}
	return {};
}

shared_ptr<AudioControls> AudioServices::createControls(string name)
{
	for (auto& p : providers) {
		auto controls = p.lock()->createControls(name);
		if (controls) {
			controls->setProviderId(p.lock()->getProviderId());
			return controls;
		}
	}
	return {};
}

string AudioServices::getAvailableControls() {
	string res;
	for (auto& p : providers) {
		res += p.lock()->getAvailableControls();
	}
	return res;
}

shared_ptr<AudioProcess> AudioServices::createProcess(weak_ptr<AudioControls> controls)
{
	for (auto& p : providers) {
		auto process = p.lock()->createProcessor(controls);
		if (process) {
			return process;
		}
	}
	return {};
}

void AudioServices::scan()
{
	auto prov = lookup(ctoot::audio::spi::AudioServiceProvider());
	providers.clear();
	for (auto& p : prov) {
		auto candidate = dynamic_pointer_cast<ctoot::audio::spi::AudioServiceProvider>(p.lock());
		if (candidate) {
			providers.push_back(candidate);
		}
	}
}

void AudioServices::accept(ctoot::service::ServiceVisitor* v, string typeIdName)
{
	for (auto& p : providers) {
		p.lock()->accept(v, typeIdName);
	}
}

void AudioServices::printServiceDescriptors(string typeIdName)
{
//    accept(new service::ServicePrinter(), clazz);
}
