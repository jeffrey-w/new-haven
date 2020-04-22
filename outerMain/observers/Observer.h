#pragma once

#include <string>

// Subscribes to Observables for updates.
class Observer {

public:

	// Destroys this Observer.
	virtual ~Observer() = default;
	// Receives notifications of changes to this Observer's subject.
	virtual void update() = 0;

};
