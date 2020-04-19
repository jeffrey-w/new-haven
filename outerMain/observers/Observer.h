#pragma once

#include <string>

// Subscribes to Observables for updates.
class Observer {

public:

	// Destroys this Observer.
	virtual ~Observer() = default;
	// Modifies the state of this Observer to reflect changes to its subject.
	virtual void update(std::string*) = 0;

};
