#include <service/Services.hpp>

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
		serviceProviders.push_back(make_shared<ctoot::synth::spi::SynthChannelServiceProvider>());
        serviceProviders.push_back(make_shared<ctoot::synth::channels::AllTootSynthChannelsServiceProvider>());
		serviceProviders.push_back(make_shared<ctoot::synth::synths::multi::MultiSynthServiceProvider>());
	}

    vector<weak_ptr<ServiceProvider>> res;

    for (auto& sp : serviceProviders)
		res.push_back(sp);

    return res;
}
