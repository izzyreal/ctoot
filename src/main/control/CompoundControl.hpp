#pragma once

#include <vector>

#include <control/Control.hpp>

namespace ctoot::control {
    class CompoundControl
            : public Control
    {
    protected:
        std::vector<std::shared_ptr<Control>> controls;
        std::vector<std::weak_ptr<Control>> weakControls;

    public:
        std::vector<std::string> getControlNamesRecursive(int generation = 0);

    public:

        virtual void add(std::shared_ptr<Control> control);

        virtual void remove(std::weak_ptr<Control> control);

    public:
        virtual std::vector<std::weak_ptr<Control>> getControls();

        virtual std::weak_ptr<Control> find(std::string name);

        virtual std::weak_ptr<Control> deepFind(int controlId);

    public:
        virtual void disambiguate(std::weak_ptr<CompoundControl> c);

        virtual void close();

        void setEnabled(bool enable) override;

    public:
        CompoundControl(int id, std::string name);
    };
}
