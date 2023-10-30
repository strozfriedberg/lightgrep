#include "lightgrep/api.h"

#include <iostream>

class Errors {
public:
    LG_Error* Err;
    LG_Error* TailErr;

    Errors(): Err(nullptr), TailErr(nullptr) {}
    ~Errors();

    void push_back(LG_Error* newErr);
    void handleParseErrors(std::ostream&, bool);
};