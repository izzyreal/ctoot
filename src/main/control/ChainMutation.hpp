#pragma once

#include <cstdint>
#include <string>
#include <memory>

namespace ctoot {
	namespace control {

		class Control;

		class ChainMutation
		{
		protected:
			std::weak_ptr<Control> control;

		public:
			static const int DELETE{ 1 };
			static const int INSERT{ 2 };
			static const int MOVE{ 3 };
			static const int COMMENCE{ 4 };
			static const int COMPLETE{ 5 };

		private:
			static ChainMutation* COMMENCE_INSTANCE_;
			static ChainMutation* COMPLETE_INSTANCE_;
			int type{};
			int index0 = -1;

		protected:
			int index1 = -1;

		public:
			virtual int getType();
			virtual int getIndex0();
			virtual int getIndex1();
			std::string toString();

		private:
			std::string typeName();

		protected:
			ChainMutation(int type);
			ChainMutation(int type, int index);

		public:
			ChainMutation(int type, int index0, int index1);
            virtual ~ChainMutation(){}

		public:
			static ChainMutation*& COMMENCE_INSTANCE();
			static ChainMutation*& COMPLETE_INSTANCE();

		};

		class DeleteMutation : public ChainMutation {
		public:
			DeleteMutation(int index);
		};

		class InsertMutation : public ChainMutation {
		public:
			InsertMutation(int index, std::weak_ptr<Control> c);
			std::weak_ptr<Control> getControl();
		};

		class MoveMutation : public ChainMutation {
		public:
			MoveMutation(int index0, int index1);
		};

	}
}
