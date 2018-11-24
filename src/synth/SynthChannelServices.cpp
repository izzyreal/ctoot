#include <synth/SynthChannelServices.hpp>

//#include <service/ServicePrinter.hpp>
#include <synth/SynthChannel.hpp>
#include <synth/SynthChannelControls.hpp>

using namespace ctoot::synth;
using namespace std;

SynthChannelServices::SynthChannelServices()
{
}
vector<weak_ptr<spi::SynthChannelServiceProvider>> SynthChannelServices::providers;

string SynthChannelServices::lookupModuleName(int32_t providerId, int32_t moduleId)
{
	for (auto& p : providers) {
		if (p.lock()->getProviderId() == providerId) {
			return p.lock()->lookupName(moduleId);
		}
	}
	return "Module not found!";
}

shared_ptr<SynthChannelControls> SynthChannelServices::createControls(const string& name)
{
	shared_ptr<SynthChannelControls> controls;
	for (auto& p : providers) {
		controls = p.lock()->createControls(name);
		if (controls) {
			controls->setProviderId(p.lock()->getProviderId());
			return controls;
		}
	}
	return {};
}

shared_ptr<SynthChannel> SynthChannelServices::createSynthChannel(weak_ptr<SynthChannelControls> controls)
{
	MLOG("Trying to create synth channel");
	for (auto& p : providers) {
		MLOG("SynthChannelProvider " + p.lock()->getProviderName() + " / " + p.lock()->getDescription());
		auto process = p.lock()->createSynthChannel(controls);
		if (process) {
			return process;
		}
	}
	return {};
}

void SynthChannelServices::scan()
{
	auto prov = lookup(spi::SynthChannelServiceProvider());
	providers.clear();
	for (auto& p : prov) {
		auto candidate = dynamic_pointer_cast<spi::SynthChannelServiceProvider>(p.lock());
		if (candidate) {
			providers.push_back(candidate);
		}
	}
}

void SynthChannelServices::accept(weak_ptr<ctoot::service::ServiceVisitor> v, const string& typeIdName)
{
	for (auto& p : providers) {
		p.lock()->accept(v, typeIdName);
	}
}

void SynthChannelServices::printServiceDescriptors(const string& typeIdName)
{
	//accept(new ctoot::service::ServicePrinter(), clazz);
}
