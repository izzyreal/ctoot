#include <synth/SynthChannelServices.hpp>

//#include <service/ServicePrinter.hpp>
#include <synth/SynthChannel.hpp>
#include <synth/SynthChannelControls.hpp>

using namespace ctoot::synth;
using namespace std;

SynthChannelServices::SynthChannelServices()
{
}
vector<weak_ptr<ctoot::synth::spi::SynthChannelServiceProvider>> SynthChannelServices::providers;

std::string ctoot::synth::SynthChannelServices::lookupModuleName(int32_t providerId, int32_t moduleId)
{
	for (auto& p : providers) {
		if (p.lock()->getProviderId() == providerId) {
			return p.lock()->lookupName(moduleId);
		}
	}
	return "Module not found!";
}

std::shared_ptr<ctoot::synth::SynthChannelControls> ctoot::synth::SynthChannelServices::createControls(std::string name)
{
	shared_ptr<ctoot::synth::SynthChannelControls> controls;
	for (auto& p : providers) {
		controls = p.lock()->createControls(name);
		if (controls) {
			controls->setProviderId(p.lock()->getProviderId());
			return controls;
		}
	}
	return {};
}

shared_ptr<ctoot::synth::SynthChannel> SynthChannelServices::createSynthChannel(weak_ptr<SynthChannelControls> controls)
{
	shared_ptr<SynthChannel> process;
	for (auto& p : providers) {
		process = p.lock()->createSynthChannel(controls);
		if (process) {
			return process;
		}
	}
	return {};
}

void SynthChannelServices::scan()
{
	auto prov = lookup(ctoot::synth::spi::SynthChannelServiceProvider());
	providers.clear();
	for (auto& p : prov) {
		auto candidate = dynamic_pointer_cast<ctoot::synth::spi::SynthChannelServiceProvider>(p.lock());
		if (candidate) {
			providers.push_back(candidate);
		}
	}
}

void SynthChannelServices::accept(ctoot::service::ServiceVisitor* v, string typeIdName)
{
	for (auto& p : providers) {
		p.lock()->accept(v, typeIdName);
	}
}

void SynthChannelServices::printServiceDescriptors(string typeIdName)
{
	//accept(new ctoot::service::ServicePrinter(), clazz);
}
