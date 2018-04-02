#include <mpc/MpcMuteInfo.hpp>

using namespace ctoot::mpc;

MpcMuteInfo::MpcMuteInfo()
{
}

void MpcMuteInfo::setNote(int note)
{
    this->note = note;
}

void MpcMuteInfo::setDrum(int drum)
{
    this->drum = drum;
}

int MpcMuteInfo::getNote()
{
    return note;
}

int MpcMuteInfo::getDrum()
{
    return drum;
}

bool MpcMuteInfo::muteMe(int note, int drum)
{
    if(this->note == note && this->drum == drum)
        return true;

    return false;
}