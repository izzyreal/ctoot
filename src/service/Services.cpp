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

Services::Services()
{
}

vector<weak_ptr<ServiceProvider>> Services::getServiceProviders() {
	static auto p1 = make_shared<ctoot::audio::reverb::ReverbServiceProvider>();
	static auto p2 = make_shared<ctoot::audio::delay::DelayServiceProvider>();
	static auto p3 = make_shared<ctoot::audio::dynamics::DynamicsServiceProvider>();
	static auto p4 = make_shared<ctoot::audio::basic::BasicServiceProvider>();
	//static auto p5 = make_shared<ctoot::synth::spi::SynthServiceProvider>();
	static auto p6 = make_shared<ctoot::synth::spi::SynthChannelServiceProvider>();
	static auto p7 = make_shared<ctoot::synth::channels::AllTootSynthChannelsServiceProvider>();
	static auto p8 = make_shared<ctoot::synth::synths::multi::MultiSynthServiceProvider>();
	static vector<weak_ptr<ServiceProvider>> res{ p1, p2, p3, p4, p6, p7, p8 };
	return res;
}

