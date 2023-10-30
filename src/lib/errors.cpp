#include "errors.h"

Errors::~Errors() {
    lg_free_error(Err);
    TailErr = nullptr;
}

void Errors::append(LG_Error* newErr) {
    if (Err) {
        TailErr->Next = newErr;
    }
    else {
        Err = newErr;
        TailErr = newErr;
    }

    for ( ; TailErr->Next; TailErr = TailErr->Next);
}

void Errors::handleParseErrors(std::ostream &out, bool printFilename) {
  LG_Error* curr = Err;
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