#pragma once

#include <iostream>

// Compares the expected expression to the the actual expression, and prints the appropriate
// message given the result. Note that equality is predicated on identity semantics unless the
// equality operator is overriden for the type of the expected and actual expressions.
#define ASSERT_EQUALS(expected, actual, success, failure) { \
	if((expected) == (actual)) \
	   std::cout << success << std::endl; \
	else \
	   std::cerr << failure << std::endl; \
}

// Evaluates the specified expression and prints the specified message if successful.
#define ASSERT_SUCCESS(expression, msg) { \
	try { \
	   (expression); \
	   std::cout << msg << std::endl; \
	} catch (...) { \
	   std::cerr << "ERROR:: exception thrown"; \
	} \
}

// Evaluates the specified expression and attempts to catch the specified exception. Should the
// expression evaluate successfully, or if an exception other than the one specified is thrown, the
// specified message is printed.
#define ASSERT_THROWS(exception, expression, msg) { \
	try { \
		(expression); \
		std::cerr << msg << std::endl; \
	} catch (exception& e) { \
		std::cout << "Successfully caught excption: "; \
		std::cout << e.what() << std::endl; \
	} catch (...) { \
		std::cerr << msg << std::endl; \
	} \
}
