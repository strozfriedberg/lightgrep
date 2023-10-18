#include "errors.h"

void Errors::append(LG_Error* new_err) {
    if (err) {
        tail_err->Next = new_err;
    }
    else {
        err = new_err;
        tail_err = new_err;
    }

    for ( ; tail_err->Next; tail_err = tail_err->Next);
}