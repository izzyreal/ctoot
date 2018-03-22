#include <service/Services.hpp>

#include <audio/reverb/ReverbServiceProvider.hpp>
#include <audio/delay/DelayServiceProvider.hpp>
#include <audio/dynamics/DynamicsServiceProvider.hpp>
#include <audio/basic/BasicServiceProvider.hpp>

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
	static vector<weak_ptr<ServiceProvider>> res{ p1, p2, p3, p4 };
	return res;
}

