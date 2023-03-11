#include <audio/system/AudioConnection.hpp>

using namespace ctoot::audio::system;
using namespace std;

AudioConnection::AudioConnection(int flags) 
{
	flags = 0;
	this->flags = flags;
}

//const int AudioConnection::PLAYBACK;
//const int AudioConnection::SYSTEM;
//const int AudioConnection::OUTPUT_LOCKED;
//const int AudioConnection::INPUT_LOCKED;

