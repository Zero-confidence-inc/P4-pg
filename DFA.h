#ifndef DFA_H
#define DFA_H

#include "Token.h"

class DFA {
public:
    virtual ~DFA() {} // Virtual destructor to allow for polymorphism
    virtual bool processChar(char c) = 0; // Process a character
    virtual Token finalizeToken() = 0; // Finalize and return the current token
    virtual bool hasToken() const = 0; // Check if there's an unfinished token
    virtual void reset() = 0; // Reset to initial state
};

#endif // DFA_H
