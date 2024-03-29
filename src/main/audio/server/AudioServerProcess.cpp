#include <audio/server/AudioServerProcess.hpp>

#include <audio/core/ChannelFormat.hpp>

using namespace ctoot::audio::server;
using namespace std;

AudioServerProcess::AudioServerProcess(string name, bool mono) {
	this->name = name;
	format = mono ? ctoot::audio::core::ChannelFormat::MONO() : ctoot::audio::core::ChannelFormat::STEREO();
}

string AudioServerProcess::getName() {
	return name;
}

std::weak_ptr<ctoot::audio::core::ChannelFormat> AudioServerProcess::getChannelFormat() {
	return format;
}
