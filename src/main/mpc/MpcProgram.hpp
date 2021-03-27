#pragma once

#include <memory>

namespace ctoot::mpc {

class MpcNoteParameters;
class MpcStereoMixerChannel;
class MpcIndivFxMixerChannel;

class MpcProgram {
    
public:
    virtual MpcNoteParameters* getNoteParameters(int i) = 0;
    virtual std::weak_ptr<MpcStereoMixerChannel> getStereoMixerChannel(int pad) = 0;
    virtual std::weak_ptr<MpcIndivFxMixerChannel> getIndivFxMixerChannel(int pad) = 0;
    
};
}
