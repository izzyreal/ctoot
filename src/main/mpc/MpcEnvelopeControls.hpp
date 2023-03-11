#pragma once
#include <control/CompoundControl.hpp>
#include <control/FloatControl.hpp>

namespace ctoot::mpc {

		class MpcEnvelopeControls
			: public ctoot::control::CompoundControl
		{

		public:
			typedef ctoot::control::CompoundControl super;

		private:
			ctoot::control::FloatControl* attackControl{ nullptr };
			ctoot::control::FloatControl* holdControl{ nullptr };
			ctoot::control::FloatControl* decayControl{ nullptr };
			float sampleRate{ 44100 };
			float attack{}, decay{}, hold{ 0 };
			int idOffset{ 0 };

		public:
			void derive(ctoot::control::Control* c) override;
			void createControls();
			void deriveSampleRateIndependentVariables();
			void deriveSampleRateDependentVariables();
			float deriveHold();
			void setSampleRate(int rate);

		private:
			static float LOG_0_01_;

		private:
			static std::weak_ptr<ctoot::control::ControlLaw> ATTACK_LAW();
			static std::weak_ptr<ctoot::control::ControlLaw> HOLD_LAW();
			static std::weak_ptr<ctoot::control::ControlLaw> DECAY_LAW();

		public:
			float deriveTimeFactor(float milliseconds);
			float deriveAttack();
			float deriveDecay();
			ctoot::control::FloatControl* createAttackControl(float init);
			ctoot::control::FloatControl* createHoldControl(float init);
			ctoot::control::FloatControl* createDecayControl(float init);

		public:
			float getAttackCoeff();
			float getHold();
			float getDecayCoeff();

		public:
			MpcEnvelopeControls(int id, std::string name, int idOffset);
        };
	}
