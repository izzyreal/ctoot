#pragma once

#include <synth/PolyphonicSynthChannel.hpp>

namespace ctoot {
	namespace synth {

		namespace modules {
			namespace oscillator {
				class MultiWaveOscillator;
				class LFOVariables;
			}
			namespace filter {
				class FilterVariables;
				class StateVariableFilterVariables;
			}
			namespace envelope {
				class EnvelopeVariables;
			}
			namespace mixer {
				class MixerVariables;
				class ModulationMixerVariables;
			}
			namespace amplifier {
				class AmplifierVariables;
			}
		}

		namespace channels {
			namespace valor {

				class ValorSynthControls;

				class ValorSynthChannel
					: public ctoot::synth::PolyphonicSynthChannel
				{

				private:
					ctoot::synth::modules::oscillator::MultiWaveOscillatorVariables* oscillator1Vars{  };
					ctoot::synth::modules::oscillator::MultiWaveOscillatorVariables* oscillator2Vars{  };
					ctoot::synth::modules::oscillator::MultiWaveOscillatorVariables* oscillator3Vars{  };
					ctoot::synth::modules::envelope::EnvelopeVariables* envelopeAVars{  };
					ctoot::synth::modules::envelope::EnvelopeVariables* envelope1Vars{  };
					ctoot::synth::modules::envelope::EnvelopeVariables* envelope2Vars{  };
					ctoot::synth::modules::envelope::EnvelopeVariables* envelopeVVars{  };
					ctoot::synth::modules::filter::FilterVariables* lpFilterVars{  };
					ctoot::synth::modules::filter::StateVariableFilterVariables* svFilterVars{  };
					ctoot::synth::modules::amplifier::AmplifierVariables* amplifierVars{  };
					ctoot::synth::modules::oscillator::LFOVariables* vibratoVars{  };
					ctoot::synth::modules::oscillator::LFOVariables* lfo1Vars{  };
					ctoot::synth::modules::oscillator::LFOVariables* lfo2Vars{  };
					ctoot::synth::modules::mixer::MixerVariables* lpFilterMixerVars{  };
					ctoot::synth::modules::mixer::MixerVariables* svFilterMixerVars{  };
					ctoot::synth::modules::mixer::ModulationMixerVariables* osc1WidthModMixer{  };
					ctoot::synth::modules::mixer::ModulationMixerVariables* osc2WidthModMixer{  };
					ctoot::synth::modules::mixer::ModulationMixerVariables* osc3WidthModMixer{  };
					ctoot::synth::modules::mixer::ModulationMixerVariables* lpfCutoffModMixer{  };
					ctoot::synth::modules::mixer::ModulationMixerVariables* svfCutoffModMixer{  };
					ctoot::synth::modules::mixer::ModulationMixerVariables* vibModMixer{  };

				protected:
					void setSampleRate(int32_t rate) override;
					ctoot::synth::PolyphonicSynthChannelVoice* createVoice(int32_t pitch, int32_t velocity, int32_t sampleRate) override;

				public:
					ValorSynthChannel(ValorSynthControls* controls);
				};

			}
		}
	}
}
