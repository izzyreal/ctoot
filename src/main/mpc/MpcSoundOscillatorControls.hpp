#pragma once
#include <control/CompoundControl.hpp>

using namespace std;

namespace ctoot::mpc {

	class MpcSoundOscillatorControls
		:
		public ctoot::control::CompoundControl
	{

	private:
		bool mono{ false }, loopEnabled{ false };
		int sampleRate{ 0 };
		int sndLevel{ 0 }, tune{ 0 };
		int start{ 0 }, end{ 0 }, loopTo{ 0 };
		vector<float> sampleData;

	public:
		void setSndLevel(int i);
		void setTune(int i);
		void setLoopEnabled(bool b);
		void setStart(int i);
		void setEnd(int i);
		void setMono(bool b);
		void setLoopTo(int i);
		int getLastFrameIndex();
		int getFrameCount();
		int getTune();
		bool isLoopEnabled();
		int getStart();
		int getEnd();
		vector<float>* getSampleData();
		bool isMono();
		int getLoopTo();
		int getSampleRate();
		void setSampleRate(int sr);
		int getSndLevel();
		void insertFrame(vector<float> frame, unsigned int index);
		void insertFrames(vector<float>& frames, unsigned int index);
		void insertFrames(vector<float>& left, vector<float>& right, unsigned int index);

	public:
		MpcSoundOscillatorControls(int id, int instanceIndex);
		~MpcSoundOscillatorControls();

	public:
		string getName();

	};
}
