#pragma once

#include <synth/PolyphonicSynthChannelAbstractVoice.hpp>

#include <vector>
#include <cstdint>

namespace ctoot {

	namespace audio {
		namespace core {
			class AudioBuffer;
		}
	}

	namespace synth {

		class PolyphonicSynthChannelAbstractVoice;

		namespace modules {
			namespace oscillator {
				class OscillatorControl;
				class MultiWaveOscillator;
				class LFO;
			}
			namespace filter {
				class MoogFilter2;
				class StateVariableFilter;
			}
			namespace envelope {
				class EnvelopeGenerator;
			}
		}

		namespace channels {
			namespace valor {

				class ValorSynthChannel;

				class Example2Voice
					: public ctoot::synth::PolyphonicSynthChannelAbstractVoice
				{

				private:
					ValorSynthChannel * vsc;
					ctoot::synth::modules::oscillator::MultiWaveOscillator* oscillator1{  };
					ctoot::synth::modules::oscillator::MultiWaveOscillator* oscillator2{  };
					ctoot::synth::modules::oscillator::MultiWaveOscillator* oscillator3{  };
					ctoot::synth::modules::filter::MoogFilter2* lpFilter{  };
					ctoot::synth::modules::filter::StateVariableFilter* svFilter{  };
					ctoot::synth::modules::envelope::EnvelopeGenerator* envelopeA{  };
					ctoot::synth::modules::envelope::EnvelopeGenerator* envelope1{  };
					ctoot::synth::modules::envelope::EnvelopeGenerator* envelope2{  };
					ctoot::synth::modules::envelope::EnvelopeGenerator* envelopeVib{  };
					ctoot::synth::modules::oscillator::LFO* lfoVib{  };
					ctoot::synth::modules::oscillator::LFO* lfo1{  };
					ctoot::synth::modules::oscillator::LFO* lfo2{  };
					ctoot::synth::modules::oscillator::OscillatorControl* oscControl{  };
					float ampT{  };
					float ampLevel{  };
					float lpfOsc1Level{  };
					float lpfOsc2Level{  };
					float lpfOsc3Level{  };
					float svfOsc1Level{  };
					float svfOsc2Level{  };
					float svfOsc3Level{  };
					bool lpfEnabled{  };
					bool svfEnabled{  };
					bool osc2Enabled{  };
					bool osc3Enabled{  };
					std::vector<float> modSamples = std::vector<float>(8);
					std::vector<float> osc1WidthModDepths{  };
					std::vector<float> osc2WidthModDepths{  };
					std::vector<float> osc3WidthModDepths{  };
					std::vector<float> lpfCutoffModDepths{  };
					std::vector<float> svfCutoffModDepths{  };
					std::vector<float> vibModDepths{  };
					float vibModPre{  };
					float fsvstatic{ 0.0f };
					float flpstatic{ 0.0f };

				public:
					void setSampleRate(int32_t rate) override;
					bool mix(ctoot::audio::core::AudioBuffer* buffer) override;

				protected:
					float getSample() override;
					virtual float modulation(int32_t start, int32_t len, std::vector<float> depths);
					bool isComplete() override;

				public:
					Example2Voice(ValorSynthChannel* vsc, int32_t pitch, int32_t velocity, int32_t sampleRate);

				};

			}
		}
	}
}
