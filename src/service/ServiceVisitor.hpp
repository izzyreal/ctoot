#pragma once

namespace ctoot {
	namespace service {

		class ServiceProvider;
		class ServiceDescriptor;
		class ServiceVisitor
		{

		public:
			virtual void visitProvider(ServiceProvider* p);
			virtual void visitDescriptor(ServiceDescriptor* d);

			ServiceVisitor();

		};
	}
}
