/*
 * Copyright 2024 Aon Cyber Solutions
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include "errors.h"

#include <iostream>

Errors::~Errors() {
  lg_free_error(Err);
}

void Errors::extend(LG_Error* newErr) {
  if (Err) {
    TailErr->Next = newErr;
  }
  else {
    Err = TailErr = newErr;
  }

  for ( ; TailErr->Next; TailErr = TailErr->Next);
}

void Errors::outputErrors(std::ostream &out, bool printFilename) {
  LG_Error* curr = Err;
  for ( ; curr; curr = curr->Next) {
    if (printFilename) {
      out << curr->Source << ", ";
    }
    out << "pattern " << curr->Index
      << " " << (curr->Pattern ? curr->Pattern : "")
      << " " << (curr->EncodingChain ? curr->EncodingChain : "")
      << ": " << curr->Message << '\n';
    }
  out.flush();
}