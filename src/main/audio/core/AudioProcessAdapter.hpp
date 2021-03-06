#pragma once
#include <audio/core/AudioProcess.hpp>

namespace ctoot::audio::core {
class AudioProcessAdapter
: public virtual AudioProcess
{
    
protected:
    AudioProcess* process;
    
public:
    void open() override;
    int processAudio(ctoot::audio::core::AudioBuffer* buf, int nFrames) override;
    void close() override;
    
    AudioProcessAdapter(AudioProcess* process);
    
};
}
