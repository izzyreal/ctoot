#pragma once

#include <memory>

/**
 * ServiceVisitor defines the Gang of Four Visitor pattern contract for
 * visiting service providers and their provided service descriptors.
 * It is provided as a class with empty implementations rather than an
 * interface so that simple implementations need override only one of
 * the methods.
 * Currently only implemented by ServicePrinter in Java toot
 */



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
