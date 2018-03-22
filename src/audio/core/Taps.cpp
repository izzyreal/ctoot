#include <audio/core/Taps.hpp>

#include <audio/core/TapControl.hpp>
#include <audio/basic/tap/TapControls.hpp>
#include <audio/core/AudioBuffer.hpp>
#include <audio/server/AudioServer.hpp>
#include <control/CompoundControl.hpp>

#include <lang/StrUtil.hpp>

#include <stdexcept>

using namespace ctoot::audio::core;
using namespace std;

void Taps::setAudioServer(ctoot::audio::server::AudioServer* s)
{
	Taps::server = s;
}

vector<ctoot::audio::basic::tap::TapControls*> Taps::taps;
ctoot::audio::server::AudioServer* Taps::server;

ctoot::audio::core::AudioBuffer* Taps::create(ctoot::audio::basic::tap::TapControls* controls)
{
	check();
	auto name = tapName(controls);
	auto buffer = server->createAudioBuffer(name);
	taps.push_back(controls);
	return buffer;
}

void Taps::remove(AudioBuffer* buffer)
{
	check();
	for (int i = 0; i < taps.size(); i++) {
		auto t = taps[i];
		if (t->getBuffer() == buffer) {
			taps.erase(taps.begin() + i);
			server->removeAudioBuffer(buffer);
			return;
		}
	}
	string errormsg = "Taps failed to remove buffer";
	printf(errormsg.c_str());
}

ctoot::audio::basic::tap::TapControls* Taps::getControls(std::string name)
{
	for (auto& t : taps) {
		auto tapname = tapName(t);
		if (name.compare(tapname) == 0) {
			return t;
		}
	}
	return nullptr;
}

ctoot::audio::core::AudioBuffer* Taps::getBuffer(std::string name)
{
	auto c = getControls(name);
	if (c == nullptr)
		return nullptr;

	return c->getBuffer();
}

void Taps::check()
{
	if (server == nullptr)
		throw std::exception("null AudioServer");
}

std::string Taps::tapName(ctoot::audio::basic::tap::TapControls* controls)
{
	vector<string> parts = moduru::lang::StrUtil::split(controls->getName(), ' ');

	auto name = controls->getParent()->getName();
	if (parts.size() > 1)
		name += parts[1];

	return name;
}
