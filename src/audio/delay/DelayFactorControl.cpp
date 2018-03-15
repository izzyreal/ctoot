#include <audio/delay/DelayFactorControl.hpp>

#include <audio/delay/AbstractDelayControls.hpp>
#include <audio/delay/NamedFactor.hpp>
#include <audio/delay/TempoDelayControls.hpp>

using namespace ctoot::audio::delay;
using namespace std;

DelayFactorControl::DelayFactorControl(TempoDelayControls *TempoDelayControls_this)
	: EnumControl(AbstractDelayControls::DELAY_FACTOR_ID, "Delay", TempoDelayControls::defaultFactor())
{
	this->TempoDelayControls_this = TempoDelayControls_this;
}


vector<boost::any> DelayFactorControl::getValues()
{
	vector<boost::any> res;
	for (auto& f : TempoDelayControls::factors()) {
		res.push_back(f);
	}
	return res;
}

void DelayFactorControl::setValue(boost::any value)
{
    super::setValue(value);
    TempoDelayControls_this->delayFactor = boost::any_cast<NamedFactor*>(value)->getFactor();
}

bool DelayFactorControl::hasLabel()
{
    return true;
}
