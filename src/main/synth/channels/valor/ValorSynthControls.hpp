#pragma once

#include <synth/SynthChannelControls.hpp>

#include <string>
#include <vector>

namespace ctoot {
	namespace synth {
		
		namespace modules {
			namespace oscillator {
				class MultiWaveOscillatorControls;
				class MultiWaveOscillatorVariables;
				class LFOControls;
			}
			namespace filter {
				class FilterControls;
				class FilterVariables;
			}
			namespace amplifier {
				class AmplifierControls;
				class AmplifierVariables;
			}
			namespace envelope {
				class EnvelopeControls;
				class EnvelopeVariables;
			}
			namespace mixer {
				class MixerControls;
				class MixerVariables;
				class ModulationMixerControls;
				class ModulationMixerVariables;
			}
		}

		namespace channels {
			
			class AllTootSynthChannelsServiceProvider;

			namespace valor {

				class ValorSynthControls
					: public ctoot::synth::SynthChannelControls
				{

				private:
					static std::string NAME;
					static constexpr int32_t OSC1_OFFSET{ int32_t(0) };
					static constexpr int32_t OSC2_OFFSET{ int32_t(8) };
					static constexpr int32_t OSC3_OFFSET{ int32_t(16) };
					static constexpr int32_t LFOVIB_OFFSET{ int32_t(24) };
					static constexpr int32_t VIB_MOD_OFFSET{ int32_t(28) };
					static constexpr int32_t LPF_OFFSET{ int32_t(32) };
					static constexpr int32_t OSC3_MOD_OFFSET{ int32_t(36) };
					static constexpr int32_t LPFMIX_OFFSET{ int32_t(40) };
					static constexpr int32_t SVFMIX_OFFSET{ int32_t(45) };
					static constexpr int32_t SVF_OFFSET{ int32_t(48) };
					static constexpr int32_t AMP_OFFSET{ int32_t(56) };
					static constexpr int32_t VIBENV_OFFSET{ int32_t(58) };
					static constexpr int32_t AMPENV_OFFSET{ int32_t(64) };
					static constexpr int32_t ENV1_OFFSET{ int32_t(72) };
					static constexpr int32_t ENV2_OFFSET{ int32_t(80) };
					static constexpr int32_t LPF_MOD_OFFSET{ int32_t(88) };
					static constexpr int32_t SVF_MOD_OFFSET{ int32_t(96) };
					static constexpr int32_t LFO1_OFFSET{ int32_t(104) };
					static constexpr int32_t OSC1_MOD_OFFSET{ int32_t(108) };
					static constexpr int32_t LFO2_OFFSET{ int32_t(112) };
					static constexpr int32_t OSC2_MOD_OFFSET{ int32_t(116) };

					std::vector<std::weak_ptr<ctoot::synth::modules::oscillator::MultiWaveOscillatorControls>> oscillatorControls{  };
					std::vector<std::weak_ptr<ctoot::synth::modules::filter::FilterControls>> filterControls{  };
					std::vector<std::weak_ptr<ctoot::synth::modules::envelope::EnvelopeControls>> envelopeControls{  };
					std::weak_ptr<ctoot::synth::modules::amplifier::AmplifierControls> amplifierControls{  };
					std::vector<std::weak_ptr<ctoot::synth::modules::oscillator::LFOControls>> lfoControls{  };
					std::vector<std::weak_ptr<ctoot::synth::modules::mixer::MixerControls>> mixerControls{  };
					std::vector<std::weak_ptr<ctoot::synth::modules::mixer::ModulationMixerControls>> modulationControls{  };

				public:
					virtual std::weak_ptr<ctoot::synth::modules::oscillator::MultiWaveOscillatorVariables> getOscillatorVariables(int32_t instance);
					virtual std::weak_ptr<ctoot::synth::modules::filter::FilterVariables> getFilterVariables(int32_t instance);
					virtual std::weak_ptr<ctoot::synth::modules::envelope::EnvelopeVariables> getEnvelopeVariables(int32_t instance);
					virtual std::weak_ptr<ctoot::synth::modules::amplifier::AmplifierVariables> getAmplifierVariables();
					virtual std::weak_ptr<ctoot::synth::modules::oscillator::LFOControls> getLFOVariables(int32_t instance);
					virtual std::weak_ptr<ctoot::synth::modules::mixer::MixerVariables> getMixerVariables(int32_t instance);
					virtual std::weak_ptr<ctoot::synth::modules::mixer::ModulationMixerVariables> getModulationMixerVariables(int32_t instance);

					ValorSynthControls();

				private:
					friend class ctoot::synth::channels::AllTootSynthChannelsServiceProvider;

				};
				REGISTER_TYPE(ctoot::synth::channels::valor::, ValorSynthControls)
			}
		}
	}
}
