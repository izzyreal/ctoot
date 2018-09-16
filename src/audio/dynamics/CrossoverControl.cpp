#include <audio/dynamics/CrossoverControl.hpp>

#include <audio/dynamics/DynamicsControlIds.hpp>
#include <control/LogLaw.hpp>

using namespace ctoot::audio::dynamics;
using namespace std;

weak_ptr<ctoot::control::ControlLaw> CrossoverControl::XO_LAW()
{
	static auto res = make_shared<ctoot::control::LogLaw>(30.0f, 10000.0f, "Hz");
	return res;
}

CrossoverControl::CrossoverControl(int idOffset, std::string name, float freq)
	: ctoot::control::FloatControl(DynamicsControlIds::CROSSOVER_FREQUENCY + idOffset, name, XO_LAW(), 1.0f, freq)
{
}

int32_t CrossoverControl::getFrequency()
{
    return static_cast< int32_t >(getValue());
}
