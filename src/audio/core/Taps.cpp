#include <audio/core/Taps.hpp>

#include <audio/core/TapControl.hpp>
#include <audio/basic/tap/TapControls.hpp>
#include <audio/core/AudioBuffer.hpp>
#include <audio/server/AudioServer.hpp>
#include <control/CompoundControl.hpp>

#include <lang/StrUtil.hpp>

#include <stdexcept>

using namespace ctoot::audio::core;
using namespace ctoot::audio::basic::tap;
using namespace std;

void Taps::setAudioServer(weak_ptr<ctoot::audio::server::AudioServer> s)
{
	Taps::server = s;
}

vector<ctoot::audio::basic::tap::TapControls*> Taps::taps;
weak_ptr<ctoot::audio::server::AudioServer> Taps::server;

ctoot::audio::core::AudioBuffer* Taps::create(ctoot::audio::basic::tap::TapControls* controls)
{
	MLOG("Taps::create is called");
	check();
	MLOG("Taps::create passed the check");
	auto name = tapName(controls);
	auto buffer = server.lock()->createAudioBuffer(name);
	MLOG("Taps::create created an audiobuffer");
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
			server.lock()->removeAudioBuffer(buffer);
			return;
		}
	}
	string errormsg = "Taps failed to remove buffer";
	printf(errormsg.c_str());
}

ctoot::audio::basic::tap::TapControls* Taps::getControls(string name)
{
	for (auto& t : taps) {
		auto tapname = tapName(t);
		
		MLOG("Checking against tapName " + tapname);
		
		if (name.compare(tapname) == 0) {
			return t;
		}
	}
	return nullptr;
}

ctoot::audio::core::AudioBuffer* Taps::getBuffer(string name)
{
	MLOG("Taps::getBuffer for " + name);
	auto c = getControls(name);
	if (c == nullptr) {
		MLOG("Taps::getBuffer for " + name + " returns nullptr");
		return nullptr;
	}
	return c->getBuffer();
}

void Taps::check()
{
	if (!server.lock())
		throw std::exception("null AudioServer");
}

string Taps::tapName(TapControls* controls)
{
	MLOG("tapName tries to make a tap name from control name " + controls->getName());
	auto parts = moduru::lang::StrUtil::split(controls->getName(), ' ');
	for (auto& p : parts) 
		MLOG("part from " + controls->getName() + ": " + p);
	
	auto name = controls->getParent()->getName();
	if (parts.size() > 1)
		name += parts[1];
	MLOG("tapName converted " + controls->getName() + " to " + name);
	return name;
}
