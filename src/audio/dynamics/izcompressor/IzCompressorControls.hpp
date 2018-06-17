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
					* BooleanControls
					*/
					bool hasRMS() override { return true; }
					bool hasMute() override { return true; }

					/*
					* FloatControls
					*/
					bool hasKnee() override { return true; }
					bool hasGain() override { return true; }
					bool hasDryGain() override { return true; }
					bool hasRatio() override { return true; }
					bool hasInputGain() override { return true; }
					bool hasOutputGain() override { return true; }
					bool hasLookAhead() override { return true; }

					bool hasHysteresis() override { return false; }
					bool hasDepth() override { return false; }
					bool hasInverseRatio() override { return false; }
					bool hasHold() override { return false; }
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
