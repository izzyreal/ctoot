#include <audio/delay/DelayBuffer.hpp>

#include <audio/core/FloatSampleBuffer.hpp>
#include <audio/delay/DelayBuffer_Filter.hpp>

#include <VecUtil.hpp>

using namespace ctoot::audio::delay;
using namespace std;

DelayBuffer::DelayBuffer(int channelCount, int sampleCount, float sampleRate)
	: ctoot::audio::core::FloatSampleBuffer(channelCount, sampleCount, sampleRate)
{
	apzm1 = vector<float>(6);
	for (int i = 0; i < 8; i++) {
        lowpass.push_back(new DelayBuffer_Filter(this));
    }
}

void ctoot::audio::delay::DelayBuffer::nudge(int on)
{
	readIndex = writeIndex;
	writeIndex += on;
	auto ns = getSampleCount();
	if (writeIndex >= ns) {
		writeIndex -= ns;
	}
}

void ctoot::audio::delay::DelayBuffer::append(int chan, float value)
{
    (*getChannel(chan))[writeIndex] = value;
}

void ctoot::audio::delay::DelayBuffer::append(ctoot::audio::core::FloatSampleBuffer* source)
{
	conform(source);
	auto count = source->getSampleCount();
	auto count2 = int(0);
	if ((writeIndex + count) > getSampleCount()) {
		count = getSampleCount() - writeIndex;
		count2 = source->getSampleCount() - count;
	}
	for (auto ch = int(0); ch < source->getChannelCount(); ch++) {
		moduru::VecUtil::VecCopy(source->getChannel(ch), 0, getChannel(ch), writeIndex, count);
	}
	if (count2 > 0) {
		for (auto ch = int(0); ch < source->getChannelCount(); ch++) {
			moduru::VecUtil::VecCopy(source->getChannel(ch), count, getChannel(ch), 0, count2);
		}
	}
	nudge(source->getSampleCount());
}

void ctoot::audio::delay::DelayBuffer::append(ctoot::audio::core::FloatSampleBuffer* source1, ctoot::audio::core::FloatSampleBuffer* source2, float level2)
{
	conform(source1);
	auto count = source1->getSampleCount();
	auto count2 = int(0);
	if ((writeIndex + count) >= getSampleCount()) {
		count = getSampleCount() - writeIndex;
		count2 = source1->getSampleCount() - count;
	}
	for (auto ch = int(0); ch < source1->getChannelCount(); ch++) {
		auto dest = getChannel(ch);
		auto src1 = source1->getChannel(ch);
		auto src2 = source2->getChannel(ch);
		for (auto i = int(0); i < count; i++) {
			(*dest)[i + writeIndex] = (*src1)[i] + level2 * (*src2)[i];
		}
	}
	if (count2 > 0) {
		for (auto ch = int(0); ch < source1->getChannelCount(); ch++) {
			auto dest = getChannel(ch);
			auto src1 = source1->getChannel(ch);
			auto src2 = source2->getChannel(ch);
			for (int i = int(0), j = count; i < count2; i++, j++) {
				(*dest)[i] = (*src1)[j] + level2 * (*src2)[j];
			}
		}
	}
	nudge(source1->getSampleCount());
}

void ctoot::audio::delay::DelayBuffer::appendFiltered(ctoot::audio::core::FloatSampleBuffer* source1, ctoot::audio::core::FloatSampleBuffer* source2, float level2, float k)
{
	conform(source1);
	lowpassK = k;
	auto count = source1->getSampleCount();
	auto count2 = int(0);
	if ((writeIndex + count) >= getSampleCount()) {
		count = getSampleCount() - writeIndex;
		count2 = source1->getSampleCount() - count;
	}
	for (auto ch = int(0); ch < source1->getChannelCount(); ch++) {
		auto lp = lowpass[ch];
		auto dest = getChannel(ch);
		auto src1 = source1->getChannel(ch);
		auto src2 = source2->getChannel(ch);
		for (auto i = int(0); i < count; i++) {
			(*dest)[i + writeIndex] = (*src1)[i] + lp->filter(level2 * (*src2)[i]);
		}
	}
	if (count2 > 0) {
		for (auto ch = int(0); ch < source1->getChannelCount(); ch++) {
			auto lp = lowpass[ch];
			auto dest = getChannel(ch);
			auto src1 = source1->getChannel(ch);
			auto src2 = source2->getChannel(ch);
			for (int i = int(0), j = count; i < count2; i++, j++) {
				(*dest)[i] = (*src1)[j] + lp->filter(level2 * (*src2)[j]);
			}
		}
	}
	nudge(source1->getSampleCount());
}

float ctoot::audio::delay::DelayBuffer::outU(int chan, int delay)
{
	auto p = readIndex - delay;
	if (p < 0)
		p += getSampleCount();

	return (*getChannel(chan))[p];
}

float ctoot::audio::delay::DelayBuffer::out(int chan, float delay)
{
    auto ns = getSampleCount();
    auto samples = getChannel(chan);
    auto d1 = static_cast< int >(delay);
    auto w = delay - d1;
    auto p1 = readIndex - d1;
    if(p1 < 0)
        p1 += ns;

    auto p2 = readIndex - d1 - int(1);
    if(p2 < 0)
        p2 += ns;

    return ((*samples)[p1] * (int(1) - w)) + ((*samples)[p2] * w);
}

float ctoot::audio::delay::DelayBuffer::outA(int chan, float delay)
{
	auto ns = getSampleCount();
	auto samples = getChannel(chan);
	auto d1 = static_cast<int>(delay);
	auto w = delay - d1;
	auto p1 = readIndex - d1;
	if (p1 < 0)
		p1 += ns;

	auto p2 = readIndex - d1 - int(1);
	if (p2 < 0)
		p2 += ns;

	return apzm1[chan] = (*samples)[p2] + ((*samples)[p1] - apzm1[chan]) * ((int(1) - w) / (int(1) + w));
}

void ctoot::audio::delay::DelayBuffer::tap(ctoot::audio::core::FloatSampleBuffer* buf, int delay, float weight)
{
	for (auto ch = int(0); ch < buf->getChannelCount(); ch++) {
		tap(ch, buf, delay, weight);
	}
}

void ctoot::audio::delay::DelayBuffer::tap(int ch, ctoot::audio::core::FloatSampleBuffer* buf, int delay, float weight)
{
	if (weight < 0.001f)
		return;

	auto sns = getSampleCount();
	auto source = getChannel(ch);
	auto dns = buf->getSampleCount();
	auto dest = buf->getChannel(ch);
	auto j = readIndex - delay + dns;
	if (j < 0)
		j += sns;

	auto count = min(sns - j, dns);
	int i;
	for (i = 0; i < count; i++) {
		(*dest)[i] += (*source)[i + j] * weight;
	}
	j = -i;
	for (; i < dns; i++) {
		(*dest)[i] += (*source)[i + j] * weight;
	}
}

void ctoot::audio::delay::DelayBuffer::conform(ctoot::audio::core::FloatSampleBuffer* buf)
{
	while (getChannelCount() < buf->getChannelCount()) {
		addChannel(true);
	}
	if (getSampleRate() != buf->getSampleRate()) {
		setSampleRate(buf->getSampleRate());
		makeSilence();
	}
}

float ctoot::audio::delay::DelayBuffer::msToSamples(float ms)
{
    return ms * getSampleRate() * 0.001f;
}

DelayBuffer::~DelayBuffer() {
	for (auto& l : lowpass) {
		if (l != nullptr)
			delete l;
	}
}