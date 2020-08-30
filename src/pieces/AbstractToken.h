#pragma once

#include <ostream>

// The base class from which all Tokens (i.e. occupants of TokenGraphs) shall be derived.
class AbstractToken {

  public:
    static constexpr int NUM_TYPES = 4;

    // Returns true iff the specified Tokens have the same type.
    static bool areSameType(AbstractToken*, AbstractToken*);
    // Ensures that the specified type is within prescribed bounds.
    static int validateType(int);

    // Destroys this AbstractToken.
    virtual ~AbstractToken() = default;
    // Returns a deep copy of this Token.
    virtual AbstractToken* clone() const = 0;
    // Returns the type of this Token.
    virtual int getType() const = 0;

    friend std::ostream& operator<<(std::ostream&, const AbstractToken&);

  protected:
    virtual std::string toString() const = 0;
};
