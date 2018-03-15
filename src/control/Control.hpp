#pragma once
#include <observer/Observable.hpp>
#include <observer/Observer.hpp>

#include <Logger.hpp>

#include <cstdint>
#include <string>
#include <map>
#include "ControlFactory.hpp"

#define REGISTER_TYPE(nspace, klass) \
    class klass##Factory : public ctoot::control::ControlFactory { \
    public: \
        klass##Factory() \
        { \
            ctoot::control::Control::registerType("class " #nspace#klass, this); \
        } \
        virtual std::shared_ptr<ctoot::control::Control> create() { \
            return std::make_shared<klass>(); \
        } \
    }; \
    static klass##Factory global_##klass##Factory;

namespace ctoot {
	namespace control {
		class CompoundControl;

		class Control : public moduru::observer::Observable
		{
		private:
			static std::map<std::string, ctoot::control::ControlFactory*>* getRegistry() {
				static std::map<std::string, ctoot::control::ControlFactory*> res;
				return &res;
			}

		public:
			static void registerType(const std::string& name, ctoot::control::ControlFactory *factory);
			static std::shared_ptr<Control> create(const std::string &name);
			
		private:
			int id;
			CompoundControl* parent{ nullptr };
			std::string name{ "" };
			std::string annotation{ "" };
			bool hidden{ false };
			bool adjusting{ false };
			bool enabled{ true };

		protected:
			bool indicator{ false };

		public:
			virtual void setHidden(bool h);
			virtual int getId();

		protected:
			CompoundControl* getParent();
			virtual void setParent(CompoundControl* c);
			virtual void notifyParent(Control* obj);
			virtual void derive(Control* obj);

		public:
			virtual std::string getName();
			virtual void setName(std::string s);
			virtual std::string getAnnotation();
			virtual void setAnnotation(std::string a);
			virtual void setIntValue(int value);
			virtual int getIntValue();
			virtual std::string getValueString();
			virtual bool isHidden();
			virtual bool isIndicator();
			virtual bool isAdjusting();
			virtual void setAdjusting(bool state);
			virtual void setEnabled(bool enable);
			virtual bool isEnabled();
			std::string toString();
			virtual std::string getControlPath();
			virtual std::string getControlPath(Control* from, std::string sep);

		protected:
			Control(int id, std::string name);
	
		public:
			virtual ~Control();

		private:
			friend class CompoundControl;
			friend class CompoundControlChain;

		};
	}
}
