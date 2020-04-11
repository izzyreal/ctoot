#pragma once

#include <audio/core/AudioControls.hpp>

namespace ctoot {
	namespace audio {

		namespace core {
			class AudioBuffer;
		}

		namespace basic {
			namespace tap {

				class TapControls
					: public ctoot::audio::core::AudioControls
				{

				private:
					int32_t refCount = 0;
					ctoot::audio::core::AudioBuffer* buffer = nullptr;

				protected:
					void setParent(ctoot::control::CompoundControl* parent) override;

				public:
					virtual void removeBuffer();
					virtual ctoot::audio::core::AudioBuffer* getBuffer();
					virtual void reference(int32_t ref);
					bool canBeDeleted() override;

				public:
					virtual bool isInactive();

				public:
					TapControls();

				};
				REGISTER_TYPE(ctoot::audio::basic::tap::, TapControls);
			}
		}
	}
}
