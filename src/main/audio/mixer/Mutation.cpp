#include <audio/mixer/Mutation.hpp>
#include <audio/mixer/MixerControls.hpp>

using namespace std;
using namespace ctoot::audio::mixer;

Mutation::Mutation
(
 int _operation,
 weak_ptr<ctoot::control::CompoundControl> _control
 ) : operation (_operation), control (_control)
{
}

const int Mutation::ADD;
const int Mutation::REMOVE;

int Mutation::getOperation()
{
    return operation;
}

weak_ptr<ctoot::control::CompoundControl> Mutation::getControl()
{
    return control;
}

string Mutation::toString()
{
    return MixerControls::opNames()[operation] + " " + control.lock()->getName();
}
