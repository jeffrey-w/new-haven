#pragma once

#include <string>

class Observer {

public:

	virtual ~Observer() = default;
	virtual void update(std::string*) = 0;

};
