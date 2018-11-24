#include <audio/spi/AudioControlServiceDescriptor.hpp>

using namespace ctoot::audio::spi;
using namespace std;

AudioControlServiceDescriptor::AudioControlServiceDescriptor(
	const string& typeIdName,
	int moduleId,
	const string& name,
	const string& description,
	const string& version)
	: ControlServiceDescriptor(typeIdName, moduleId, name, description, version)
{
}

AudioControlServiceDescriptor::AudioControlServiceDescriptor(
	const string& typeIdName,
	int moduleId,
	const string& name,
	const string& description,
	const string& version,
	std::weak_ptr<ctoot::audio::core::ChannelFormat> format,
	const string& path)
	: ControlServiceDescriptor(typeIdName, moduleId, name, description, version)
{
	channelFormat = format;
	pluginPath = path;
}

std::weak_ptr<ctoot::audio::core::ChannelFormat> AudioControlServiceDescriptor::getChannelFormat()
{
    return channelFormat;
}

string AudioControlServiceDescriptor::getPluginPath()
{
    return pluginPath;
}
