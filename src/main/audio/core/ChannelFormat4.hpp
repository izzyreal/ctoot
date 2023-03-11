#pragma once
#include <audio/core/ChannelFormat.hpp>
#include <cstdint>

namespace ctoot {
	namespace audio {
		namespace core {

			class ChannelFormat4 final
				: public ChannelFormat
			{

			private:
				std::vector<int8_t> left{ 0, 2 };
				std::vector<int8_t> right{ 1, 3 };

			public:
				int getCount() override;

                std::vector<int8_t> getLeft() override;
				std::vector<int8_t> getRight() override;
				std::string getName() override;
				std::string getName(int chan) override;
				ChannelFormat4();
			};
		}
	}
}
