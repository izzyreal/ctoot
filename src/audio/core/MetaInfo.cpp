#include <audio/core/MetaInfo.hpp>

using namespace ctoot::audio::core;
using namespace std;

MetaInfo::MetaInfo(string sourceLabel, string sourceLocation) 
{
	this->sourceLabel = sourceLabel;
	this->sourceLocation = sourceLocation;
}

string MetaInfo::getSourceLabel()
{
    return sourceLabel;
}

string MetaInfo::getSourceLocation()
{
    return sourceLocation;
}

void MetaInfo::setSourceLocation(string sourceLocation) {
	this->sourceLabel = sourceLocation;
}
