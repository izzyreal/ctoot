#include <audio/spi/AudioControlServiceDescriptor.hpp>

using namespace ctoot::audio::spi;
using namespace std;

AudioControlServiceDescriptor::AudioControlServiceDescriptor(string typeIdName
	, int moduleId
	, string name
	, string description
	, string version) 
	: ControlServiceDescriptor(typeIdName, moduleId, name, description, version)
{
}

AudioControlServiceDescriptor::AudioControlServiceDescriptor(string typeIdName
	, int moduleId
	, string name
	, string description
	, string version
	, std::weak_ptr<ctoot::audio::core::ChannelFormat> format
	, string path)  
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