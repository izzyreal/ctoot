#include <service/Services.hpp>

#include <audio/reverb/ReverbServiceProvider.hpp>
#include <audio/delay/DelayServiceProvider.hpp>
#include <audio/dynamics/DynamicsServiceProvider.hpp>
#include <audio/basic/BasicServiceProvider.hpp>
#include <synth/spi/SynthServiceProvider.hpp>
#include <synth/spi/SynthChannelServiceProvider.hpp>
#include <synth/channels/AllTootSynthChannelsServiceProvider.hpp>
#include <synth/synths/multi/MultiSynthServiceProvider.hpp>

using namespace std;
using namespace ctoot::service;

std::vector<std::shared_ptr<ServiceProvider>> Services::serviceProviders;

Services::Services()
{
}

vector<weak_ptr<ServiceProvider>> Services::getServiceProviders() {
	if (serviceProviders.size() == 0) {
		MLOG("making serviceproviders");
		serviceProviders.push_back(make_shared<ctoot::audio::reverb::ReverbServiceProvider>());
		serviceProviders.push_back(make_shared<ctoot::audio::delay::DelayServiceProvider>());
		serviceProviders.push_back(make_shared<ctoot::audio::dynamics::DynamicsServiceProvider>());
		serviceProviders.push_back(make_shared<ctoot::audio::basic::BasicServiceProvider>());
		serviceProviders.push_back(make_shared<ctoot::synth::spi::SynthChannelServiceProvider>());
        serviceProviders.push_back(make_shared<ctoot::synth::channels::AllTootSynthChannelsServiceProvider>());
		serviceProviders.push_back(make_shared<ctoot::synth::synths::multi::MultiSynthServiceProvider>());
	}
	MLOG("Service providers:");
	for (auto& sp : serviceProviders)
		MLOG(sp->getDescription() + ", " + sp->getProviderName());
	vector<weak_ptr<ServiceProvider>> res;
	for (auto& sp : serviceProviders)
		res.push_back(sp);
	return res;
}
