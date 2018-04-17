#pragma once
#include <audio/dynamics/CompressorControls.hpp>

#include <string>

namespace ctoot {
	namespace audio {
		namespace dynamics {
			namespace izcompressor {

				class IzCompressorControls
					: public CompressorControls
				{

				protected:

					/*
					* Non-controllable, just for metering purposes
					*/
					bool hasGainReductionIndicator() override { return true; }

					/*
					* Sidechain
					*/
					bool hasKey() override { return true; }

					/*
					* BooleanControl to switch between RMS and peak
					*/
					bool hasRMS() override { return true; }

					/*
					* FloatControls
					*/
					// attack is implicit
					// release is implicit
					// threshold is implicit
					bool hasKnee() override { return true; }
					bool hasGain() override { return true; }
					bool hasDryGain() override { return true; }
					bool hasRatio() override { return true; }
					bool hasInputGain() override { return true; }
					// mix needs to be implemented
					// look ahead needs to be implemented
					bool hasLookAhead() override { return true; }

					bool hasHysteresis() override { return false; } // only used for gates
					bool hasDepth() override { return false; } // applies a limit to the amount of attenuation
					bool hasInverseRatio() override { return false; }; // allows for expansion of the signal?
					bool hasHold() override { return false; } // currently not needed for our purposes

					bool hasChannelMode() override { return true; } // To select M,S,L,R,LR

				public:
					bool canBypass() override { return true; }

				public:
					IzCompressorControls(std::string name, int32_t idOffset);

				};
			}
		}
	}
}
