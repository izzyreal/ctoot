#pragma once

#include "ServiceProvider.hpp"

#include <Logger.hpp>

#include <memory>
#include <vector>
#include <string>

namespace ctoot {
	namespace service {

		class Services
		{

		private:
			static std::vector<std::weak_ptr<ServiceProvider>> getServiceProviders();

		public:
			template <typename T>
			static std::vector<std::weak_ptr<ServiceProvider>> lookup(T clazz)
			{
				std::string clazzName = typeid(clazz).name();
				vector<weak_ptr<ServiceProvider>> res;
				for (auto& p : getServiceProviders()) {
					if (dynamic_pointer_cast<T>(p.lock())) {
						res.push_back(p);
					}
				}
				return res;
			}

		public:
			Services();

		};
	}
}
