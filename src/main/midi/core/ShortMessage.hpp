#pragma once
#include <midi/core/MidiMessage.hpp>

#include <vector>

namespace ctoot::midi::core {
class ShortMessage final
: public MidiMessage
{
    
public:
    static const int CHANNEL_PRESSURE{ 208 };
    static const int CONTINUE{ 251 };
    static const int CONTROL_CHANGE{ 176 };
    static const int NOTE_OFF{ 128 };
    static const int NOTE_ON{ 144 };
    static const int POLY_PRESSURE{ 160 };
    static const int START{ 250 };
    static const int STOP{ 252 };
    static const int TIMING_CLOCK{ 248 };

public:
    virtual int getChannel();
    virtual int getCommand();
    virtual int getData1();
    virtual int getData2();
    
public:
    int getDataLength(int status);
    
public:
    virtual void setMessage(int status);
    virtual void setMessage(int status, int data1, int data2);
    virtual void setMessage(int command, int channel, int data1, int data2);
    
    ShortMessage();
    ShortMessage(const std::vector<char>& data);
    
public:
    virtual void setMessage(const std::vector<char>& data, int length);
    
};
}
