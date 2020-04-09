#pragma once

// Forward Declaration.
class Event;

class Observer {

public:

	virtual ~Observer() = default;
	virtual void update(Event) = 0;

};
