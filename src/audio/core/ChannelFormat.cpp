#include <audio/core/ChannelFormat.hpp>
#include <audio/core/ChannelFormat1.hpp>
#include <audio/core/ChannelFormat2.hpp>
#include <audio/core/ChannelFormat3.hpp>
#include <audio/core/ChannelFormat4.hpp>
#include <audio/core/AudioBuffer.hpp>

#include <cstdint>

using namespace std;
using namespace ctoot::audio::core;

ChannelFormat::ChannelFormat()
{
}

int ChannelFormat::mix(ctoot::audio::core::AudioBuffer* destBuffer, ctoot::audio::core::AudioBuffer* sourceBuffer, vector<float> gain)
{
	auto doMix = destBuffer != sourceBuffer;
	auto snc = sourceBuffer->getChannelCount();
	auto dnc = destBuffer->getChannelCount();
	if (dnc > 4 && snc != dnc) dnc = 4;

	auto ns = destBuffer->getSampleCount();
	float g;
	auto k = static_cast<float>((snc)) / dnc;
	vector<float>* in;
	vector<float>* out;
	for (auto i = 0; i < dnc; i++) {
		g = gain[i] * k;
		in = sourceBuffer->getChannel(i % snc);
		out = destBuffer->getChannel(i);
		if (doMix) {
			for (auto s = 0; s < ns; s++) {
				(*out)[s] += (*in)[s] * g;
			}
		}
		else {
			for (auto s = 0; s < ns; s++) {
				(*out)[s] = (*in)[s] * g;
			}
		}
	}
	auto ret = 1;
	if (!doMix) ret |= 2;
	return ret;
}

weak_ptr<ChannelFormat> ChannelFormat::MONO() {
	static shared_ptr<ChannelFormat> monoChannelFormat = make_shared<ChannelFormat1>();
	return monoChannelFormat;
}

weak_ptr<ChannelFormat> ChannelFormat::STEREO() {
	static shared_ptr<ChannelFormat> stereoChannelFormat = make_shared<ChannelFormat2>();
	return stereoChannelFormat;
}

weak_ptr<ChannelFormat> ChannelFormat::QUAD() {
	static shared_ptr<ChannelFormat> stereoChannelFormat = make_shared<ChannelFormat2>();
	return stereoChannelFormat;
}

weak_ptr<ChannelFormat> ChannelFormat::FIVE_1() {
	static shared_ptr<ChannelFormat> stereoChannelFormat = make_shared<ChannelFormat2>();
	return stereoChannelFormat;
}
