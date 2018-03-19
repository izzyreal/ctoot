#include <audio/dynamics/CrossoverSection.hpp>

#include <audio/dynamics/CrossoverControl.hpp>
#include <dsp/filter/FilterShape.hpp>

using namespace ctoot::audio::dynamics;

CrossoverSection::CrossoverSection(CrossoverControl* control, ctoot::dsp::filter::FilterShape type)
{
    this->control = control;
    this->shape = type;
}

int32_t CrossoverSection::getFrequency()
{
	return control->getFrequency();
}

ctoot::dsp::filter::FilterShape CrossoverSection::getShape()
{
    return shape;
}

float CrossoverSection::getResonance()
{
    return 0.707f;
}

float CrossoverSection::getLeveldB()
{
    return 0.0f;
}

float CrossoverSection::getLevelFactor()
{
    return 1.0f;
}

bool CrossoverSection::is4thOrder()
{
    return false;
}

void CrossoverSection::addObserver(moduru::observer::Observer* o)
{
    control->addObserver(o);
}

void CrossoverSection::deleteObserver(moduru::observer::Observer* o)
{
    control->deleteObserver(o);
}
