#include "MpcIndivFxMixerChannel.hpp"

using namespace ctoot::mpc;
using namespace std;

MpcIndivFxMixerChannel::MpcIndivFxMixerChannel() 
{
	output = 0;
	volumeIndividualOut = 100;
	fxPath = 0;
	fxSendLevel = 0;
	followStereo = false;
}

void MpcIndivFxMixerChannel::setFollowStereo(bool b)
{
	if (followStereo == b) return;

	followStereo = b;
	setChanged();
	notifyObservers(string("followstereo"));
}

bool MpcIndivFxMixerChannel::isFollowingStereo()
{
    return followStereo;
}

int MpcIndivFxMixerChannel::getOutput()
{
    return output;
}

void MpcIndivFxMixerChannel::setOutput(int i)
{
	if (i < 0 || i > 8)
		return;

	output = i;
	setChanged();
	notifyObservers(string("output"));
}

void MpcIndivFxMixerChannel::setVolumeIndividualOut(int i)
{
	if (i < 0 || i > 100)
		return;

	volumeIndividualOut = i;
	setChanged();
	notifyObservers(string("volumeindividual"));
}

int MpcIndivFxMixerChannel::getVolumeIndividualOut()
{
    return volumeIndividualOut;
}

void MpcIndivFxMixerChannel::setFxPath(int i)
{
	if (i < 0 || i > 4)
		return;

	fxPath = i;
	setChanged();
	notifyObservers(string("fxpath"));
}

int MpcIndivFxMixerChannel::getFxPath()
{
    return fxPath;
}

void MpcIndivFxMixerChannel::setFxSendLevel(int i)
{
	if (i < 0 || i > 100)
		return;

	fxSendLevel = i;
	setChanged();
	notifyObservers(string("fxsendlevel"));
}

int MpcIndivFxMixerChannel::getFxSendLevel()
{
    return fxSendLevel;
}
