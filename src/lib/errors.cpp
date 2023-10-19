#include "errors.h"

Errors::Errors(LG_Error* err) {
    this->err = err;
    tail_err = err;
    for ( ; tail_err->Next; tail_err = tail_err->Next);
}

Errors::~Errors() {
    LG_Error* temp;
    while (err != tail_err) {
        temp = err;
        err = err->Next;
        delete temp;
    }
    delete err;
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