#pragma once

#include <string>

#include "../observers/Observable.h"
#include "../observers/Observer.h"

// Observes a New Haven object.
class View : public Observer {

  public:
    // Constructs a new View object and registers it with the specified Observable. Throws an
    // exception if the specified Observable is null.
    View(Observable*, std::string*);
    // Supress copy constructor.
    View(const View&) = delete;
    // Destroys this View.
    ~View();
    // Displays the subject of this View.
    void show(const std::string* = nullptr) const;
    // Modifies the state of this View to reflect changes to its subject.
    void update() override;

  private:
    Observable* subject;
    std::string* header;
};
