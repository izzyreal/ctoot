#pragma once
#include <synth/SynthControls.hpp>
#include <synth/SynthChannelControls.hpp>
#include <cstdint>
#include <string>

namespace ctoot {
	namespace synth {

		class ChannelledSynthControls
			: public SynthControls
		{

		public:
			typedef SynthControls super;

		private:
            std::vector<std::weak_ptr<SynthChannelControls>> channelControls{};

		public:
            virtual std::weak_ptr<SynthChannelControls> getChannelControls(int chan);

		public:
            virtual void setChannelControls(int chan, std::shared_ptr<SynthChannelControls> controls);

		public:
			ChannelledSynthControls(int id, std::string name);
			
			virtual ~ChannelledSynthControls();

		};

	}
}
