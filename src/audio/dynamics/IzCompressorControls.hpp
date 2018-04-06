#pragma once
#include <audio/dynamics/CompressorControls.hpp>

#include <string>

namespace ctoot {
	namespace audio {
		namespace dynamics {

			class IzCompressorControls
				: public CompressorControls
			{

			protected:

				/*
				* Non-controllable, just for metering purposes
				*/
				bool hasGainReductionIndicator() override { return true; };

				/*
				* Sidechain
				*/
				bool hasKey() override { return true; };

				/*
				* BooleanControl to switch between RMS and peak
				*/
				bool hasRMS() override { return true; };

				/*
				* FloatControls
				*/
				// attack is implicit
				// release is implicit
				// threshold is implicit
				bool hasKnee() override { return true; };
				bool hasGain() override { return true; }; // make up gain
				bool hasDryGain() override { return false; }; // output gain
				bool hasRatio() override { return true; };
				// mix needs to be implemented
				// look ahead needs to be implemented
				// input gain needs to be implemented

				bool hasHysteresis() override { return false; }; // does something based on the history of the signal?
				bool hasDepth() override { return false; }; // applies a limit to the amount of attenuation
				bool hasInverseRatio() override { return false; }; // allows for expansion of the signal?
				bool hasHold() override { return false; }; // currently not needed for our purposes

			public:
				bool canBypass() override { return true; };

			public:
				IzCompressorControls(std::string name, int32_t idOffset);

			};
		}
	}
}
