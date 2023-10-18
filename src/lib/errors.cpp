#include "errors.h"

Errors::Errors(LG_Error* err) {
    this->err = err;
    for ( ; err; err = err->Next) {
        tail_err = err;
    }
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
    for ( ; err; err = err->Next) {
    if (printFilename) {
      out << err->Source << ", ";
    }
    out << "pattern " << err->Index
        << " " << (err->Pattern? err->Pattern : "") 
        << " " << (err->EncodingChain? err->EncodingChain : "")
        << ": " << err->Message << '\n';
  }
  out.flush();
}