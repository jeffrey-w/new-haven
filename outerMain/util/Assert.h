#pragma once

#include <iostream>

// Compares the expected expression to the the actual expression, printing the specified message if
// they are not equal. Note that equality is predicated on identity semantics.
#define ASSERT_EQUALS(expected, actual, msg) { \
    if((expected) != (actual)) \
       std::cerr << msg << std::endl; \
}

// Evaluates the specified expression and attempts to catch the specified exception. Should the
// expression evaluate successfully, or if an exception other than the one specified is thrown, the
// specified message is printed.
#define ASSERT_THROWS(exception, expression, msg) { \
    try { \
        (expression); \
        std::cerr << msg << std::endl; \
    } catch (exception& e) { \
        std::cerr << e.what() << std::endl; \
    } catch (...) { \
        std::cerr << msg << std::endl; \
    } \
}
