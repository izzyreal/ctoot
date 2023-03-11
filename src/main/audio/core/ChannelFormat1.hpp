#pragma once
#include <cstdint>
#include <audio/core/ChannelFormat.hpp>

namespace ctoot {
	namespace audio {
		namespace core {

			class ChannelFormat1 final
				: public ChannelFormat
			{

			private:
				std::vector<int8_t> empty{ 1 };

			public:
				int getCount() override;

                int getCenter() override;
				int getLFE() override;
				std::vector<int8_t> getLeft() override;
				std::vector<int8_t> getRight() override;
				std::string getName() override;
				std::string getName(int chan) override;
				ChannelFormat1();

			private:
				friend class ChannelFormat;
			};

		}
	}
}
