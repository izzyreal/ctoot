#include <audio/core/AudioBuffer.hpp>
#include <audio/core/ChannelFormat.hpp>

using namespace ctoot::audio::core;
using namespace std;

AudioBuffer::AudioBuffer(string name, int channelCount, int sampleCount, float sampleRate) : FloatSampleBuffer(channelCount, sampleCount, sampleRate)
{
	this->name = name;
	realTime = true;
	channelFormat = guessFormat();
}

const bool AudioBuffer::isSilent() {
    for (int c = 0; c < getChannelCount(); c++) {
        auto data = *getChannel(c);
        for (int s = 0; s < getSampleCount(); s++) {
            if (data[s] != 0) return false;
        }
    }
    return true;
}

string AudioBuffer::getName()
{
   return name;
}

void AudioBuffer::setChannelCount(int count)
{
	if (count == getChannelCount()) return;

	if (count < getChannelCount()) {
		for (auto ch = getChannelCount() - 1; ch > count - 1; ch--) {
			removeChannel(ch);
		}
	}
	else {
		while (getChannelCount() < count) {
			addChannel(false);
		}
	}
}


void AudioBuffer::setMetaInfo(weak_ptr<MetaInfo> info)
{
    //metaInfo = info;
}

weak_ptr<MetaInfo> AudioBuffer::getMetaInfo()
{
    return metaInfo;
}

bool AudioBuffer::isRealTime()
{
    return realTime;
}

void AudioBuffer::setRealTime(bool realTime)
{
    this->realTime = realTime;
}


weak_ptr<ChannelFormat> AudioBuffer::guessFormat()
{
    switch (getChannelCount()) {
    case 1:
        return ChannelFormat::MONO();
    case 2:
        return ChannelFormat::STEREO();
    case 4:
        return ChannelFormat::QUAD();
    case 6:
        return ChannelFormat::FIVE_1();
    }
    return ChannelFormat::STEREO();
}

weak_ptr<ChannelFormat> AudioBuffer::getChannelFormat()
{
    return channelFormat;
}

void AudioBuffer::setChannelFormat(weak_ptr<ChannelFormat> newFormat)
{
    auto l_newFormat = newFormat.lock();
    auto l_channelFormat = channelFormat.lock();

    if (l_newFormat == l_channelFormat) {
        return;
    }

	channelFormat = l_newFormat;

	if (l_newFormat) {
		setChannelCount(l_newFormat->getCount());
	}
}


void AudioBuffer::convertTo(weak_ptr<ChannelFormat> format)
{
	if (channelFormat.lock() == format.lock())
		return;

	if (format.lock()->getCount() == 1) {
		mixDownChannels();
		channelFormat = format;
	}
	else if (channelFormat.lock()->getCount() == 1) {
		auto nc = format.lock()->getCount();
		auto ns = getSampleCount();
		auto samples = getChannel(0);
		auto gain = 1.0f / nc;
		for (auto s = 0; s < ns; s++) {
			(*samples)[s] *= gain;
		}
		expandChannel(nc);
		channelFormat = format;
	}
	else {
		//auto convertingFormat = channelFormat.lock()->getCount() > format.lock()->getCount() ? channelFormat : format;
		// currently not implemented, see java toot
	}
}


void AudioBuffer::monoToStereo()
{
	if (getChannelCount() < 2) {
		convertTo(ChannelFormat::STEREO());
	}
}

void AudioBuffer::swap(int a, int b)
{
    auto ns = getSampleCount();
    auto asamples = getChannel(a);
    auto bsamples = getChannel(b);
    float tmp;
    for (auto s = 0; s < ns; s++) {
        tmp = (*asamples)[s];
        (*asamples)[s] = (*bsamples)[s];
        (*bsamples)[s] = tmp;
    }
}

float AudioBuffer::square()
{
	auto ns = getSampleCount();
	auto nc = getChannelCount();
	auto sumOfSquares = 0.0f;
	vector<float>* samples;
	for (auto c = 0; c < nc; c++) {
		samples = getChannel(c);
		for (auto s = 0; s < ns; s++) {
			auto sample = (*samples)[s];
			sumOfSquares += sample * sample;
		}
	}
	return sumOfSquares / (nc * ns);
}

bool AudioBuffer::encodeMidSide()
{
	auto lefts = channelFormat.lock()->getLeft();
    auto rights = channelFormat.lock()->getRight();

	if (lefts.size() == 0)
        return false;

	auto np = lefts.size();
    auto ns = getSampleCount();
    for (auto p = 0; p < np; p++) {
        auto left = getChannel(lefts[p]);
        auto right = getChannel(rights[p]);
        for (auto s = 0; s < ns; s++) {
            auto mid = 0.5f * ((*left)[s] + (*right)[s]);
            auto side = 0.5f * ((*left)[s] - (*right)[s]);
            (*left)[s] = mid;
            (*right)[s] = side;
        }
    }
	return true;
}


bool AudioBuffer::decodeMidSide()
{
	auto mids = channelFormat.lock()->getLeft();
    auto sides = channelFormat.lock()->getRight();
    if (mids.size() == 0)
        return false;

	auto np = mids.size();
    auto ns = getSampleCount();
    for (auto p = 0; p < np; p++) {
        auto mid = getChannel(mids[p]);
        auto side = getChannel(sides[p]);
        for (auto s = 0; s < ns; s++) {
            auto left = (*mid)[s] + (*side)[s];
            auto right = (*mid)[s] - (*side)[s];
            (*mid)[s] = left;
            (*side)[s] = right;
        }
    }
    return true;
}

void AudioBuffer::copyFrom(AudioBuffer* src)
{
    if(src == nullptr) return;

    setChannelFormat(src->getChannelFormat());
    auto nc = getChannelCount();
    auto ns = getSampleCount();
    for (auto c = 0; c < nc; c++) {
        auto from = src->getChannel(c);
        auto to = getChannel(c);
        for (auto s = 0; s < ns; s++) {
           (*to)[s] = (*from)[s];
        }
    }
}

AudioBuffer::~AudioBuffer() {
}
