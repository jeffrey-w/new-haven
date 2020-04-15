#pragma once

#include <string>

#include "../observers/Observable.h"
#include "../observers/Observer.h"

class View : public Observer {

public:

	View(Observable*);
	View(const View&) = delete;
	~View();
	void show() const;
	void update(std::string*) override;

private:

	std::string* rep;

};

