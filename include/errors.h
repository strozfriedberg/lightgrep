#include "lightgrep/api.h"

#include <memory>

class Errors {
public:
    LG_Error* err;
    LG_Error* tail_err;

    Errors() { err = nullptr; tail_err = nullptr; }
    void append(LG_Error* new_err);
};