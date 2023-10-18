#include "lightgrep/api.h"

#include <iostream>

class Errors {
public:
    LG_Error* err;
    LG_Error* tail_err;

    Errors() { err = nullptr; tail_err = nullptr; }
    Errors(LG_Error*);
    ~Errors();

    void append(LG_Error* new_err);
    void handleParseErrors(std::ostream&, bool);
};