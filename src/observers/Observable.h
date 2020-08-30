#pragma once

#include <set>
#include <string>

#include "Observer.h"

// A subject to Observers.
class Observable {

  public:
    // Constructs a new Observable object.
    Observable();
    // Destroys this Observable.
    ~Observable();
    // Registers the speficied Observer with this Observable. Throws an exception if the specified
    // Observer is null.
    void attach(Observer*);
    // Deregisters the specified Observer with this Observable.
    void detach(Observer*);
    // Updates the Observers registered with this Observable.
    void notify();

    friend std::ostream& operator<<(std::ostream&, const Observable&);

  protected:
    virtual std::string toString() const = 0;

  private:
    std::set<Observer*>* observers;
};
