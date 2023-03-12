#pragma once

#include <observer/Observable.hpp>
#include <observer/Observer.hpp>

#include <Logger.hpp>

#include <cstdint>
#include <string>
#include <map>

namespace ctoot::control {
    class CompoundControl;

    class Control : public moduru::observer::Observable
    {
    private:
        int id;
        CompoundControl *parent{nullptr};
        std::string name;
        std::string annotation;
        bool hidden{false};
        bool enabled{true};

    protected:
        bool indicator{false};

    public:
        virtual void setHidden(bool h);

        virtual int getId();

        CompoundControl *getParent();

    protected:
        virtual void setParent(CompoundControl *c);

        virtual void notifyParent(Control *obj);

        virtual void derive(Control *obj);

    public:
        virtual std::string getName();

        virtual void setName(std::string s);

        virtual void setAnnotation(std::string a);

        virtual int getIntValue();

        virtual std::string getValueString();

        virtual bool isHidden();

        virtual bool isIndicator();

        virtual void setEnabled(bool enable);

        virtual bool isEnabled();

        std::string toString();

        virtual std::string getControlPath(Control *from, std::string sep);

    protected:
        Control(int id, std::string name);

    public:
        virtual ~Control();

    private:
        friend class CompoundControl;

        friend class CompoundControlChain;

    };
}
