#pragma once

#include <control/CompoundControl.hpp>
#include <vector>

using namespace std;

namespace ctoot {
	namespace control {
		class CompoundControlChain
			: public CompoundControl
		{

		public:
			virtual void add(shared_ptr<Control> control) override;
			virtual void add(int index, shared_ptr<Control> control);
			void insert(string insertName, string insertBeforeName);
			void insert(shared_ptr<Control> controlToInsert, string insertBeforeName);

		public:
			virtual shared_ptr<CompoundControl> createControl(string name);

		public:
			void delete_(string deleteName);
			void delete_(int indexToDelete);
			void move(string moveName, string moveBeforeName);
			void setMutating(bool mutating);
			bool isPluginParent() override;

		public:
			CompoundControlChain(int id, string name);
			CompoundControlChain(int id, int index, string name);
			virtual ~CompoundControlChain();

		};

	}
}
