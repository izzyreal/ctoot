#pragma once
#include <audio/core/AudioProcess.hpp>
#include <audio/core/AudioControlsChain.hpp>
#include <audio/core/AudioControls.hpp>

#include <observer/Observer.hpp>
#include <thirdp/concurrentqueue.h>

#include <cstdint>

namespace ctoot {

	namespace control {
		class ChainMutation;
	}

	namespace audio {
		namespace core {

			class AudioProcessChain
				: public virtual AudioProcess
			{

			public:
				std::weak_ptr<AudioControlsChain> controlChain;
				std::vector<std::shared_ptr<AudioProcess>> processes;

			private:
				moodycamel::ConcurrentQueue<ctoot::control::ChainMutation*> mutationQueue {};
				moduru::observer::Observer* controlChainObserver{ nullptr };
				bool debugTimes{ false };
				std::vector <int64_t> t{};

			public:
				void open() override;

			private:
				int debugIndex{};
				int64_t prevNanos{};
				int64_t tstart{};
				int64_t elapsed{};

			public:
				int processAudio(ctoot::audio::core::AudioBuffer* buffer) override;
				virtual int debugProcessAudio(ctoot::audio::core::AudioBuffer* buffer);
				void close() override;
				virtual std::string getName();

			public:
				virtual std::shared_ptr<AudioProcess> createProcess(std::weak_ptr<AudioControls> controls);
				virtual void processMutations();

			public:
				AudioProcessChain(std::weak_ptr<AudioControlsChain> controlChain);
				~AudioProcessChain();

			private:
				friend class ControlChainObserver;

			};

		}
	}
}
