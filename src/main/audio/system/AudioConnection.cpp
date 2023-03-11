#include <audio/system/AudioConnection.hpp>

using namespace ctoot::audio::system;
using namespace std;

AudioConnection::AudioConnection(int flags) 
{
	flags = 0;
	this->flags = flags;
}
