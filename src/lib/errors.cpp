#include "errors.h"

Errors::~Errors() {
    lg_free_error(err);
}

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

void Errors::handleParseErrors(std::ostream &out, bool printFilename) {
  LG_Error* curr = err;
  for ( ; curr; curr = curr->Next) {
    if (printFilename) {
        out << curr->Source << ", ";
    }
    out << "pattern " << curr->Index
        << " " << (curr->Pattern? curr->Pattern : "")
        << " " << (curr->EncodingChain? curr->EncodingChain : "")
        << ": " << curr->Message << '\n';
    }
  out.flush();
}