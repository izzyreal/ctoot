#pragma once

#include <control/CompoundControl.hpp>

namespace ctoot::control
{
	class CompoundControlChain
		: public CompoundControl
	{

	public:
		virtual void add(std::shared_ptr<Control> control) override;
		virtual void add(int index, std::shared_ptr<Control> control);
		void insert(std::string insertName, std::string insertBeforeName);
		void insert(std::shared_ptr<Control> controlToInsert, std::string insertBeforeName);

	public:
		virtual std::shared_ptr<CompoundControl> createControl(std::string name);

	public:
        void move(std::string moveName, std::string moveBeforeName);

    public:
		CompoundControlChain(int id, std::string name);
		CompoundControlChain(int id, int index, std::string name);
		virtual ~CompoundControlChain() override;

	};
}
