#pragma once

#include <audio/core/SimpleAudioProcess.hpp>

#include <audio/basic/trim/TrimControls.hpp>

#include <memory>

using namespace ctoot::audio::core;

using namespace std;

namespace ctoot::audio::basic::trim {

	class TrimProcess
		: public SimpleAudioProcess {

	private:
		weak_ptr<TrimControls> controls;

	public:
		int processAudio(AudioBuffer* buffer) override;

	public:
		TrimProcess(weak_ptr<TrimControls> controls);
		~TrimProcess();

	};

}