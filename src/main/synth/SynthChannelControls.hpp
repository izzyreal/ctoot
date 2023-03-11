#pragma once

#include <synth/ControlChange.hpp>
#include <control/CompoundControl.hpp>

#include <observer/Observer.hpp>
#include <thirdp/concurrentqueue.h>

namespace ctoot {
	namespace synth {

		class SynthChannelControls
			: public ctoot::control::CompoundControl
			, public moduru::observer::Observer
		{

		private:
			bool learn{ false };
			ctoot::control::Control* learnControl{ nullptr };
			std::vector<ctoot::control::Control*> map{};
			moodycamel::ConcurrentQueue<ControlChange*> changeQueue{};
			//std::thread* changeThread { nullptr };
			moduru::observer::Observable* observable{ nullptr };

		public:
			void close() override;

		public:
			void notifyParent(ctoot::control::Control* obj) override;
			virtual void ensureMapExists();

		public:
			void update(moduru::observer::Observable* o, nonstd::any a) override;
			//    void run() override;

        public:
			SynthChannelControls(int id, std::string name);
			virtual ~SynthChannelControls();

		};

	}
}
