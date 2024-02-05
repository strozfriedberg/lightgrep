#include "lightgrep/api.h"

#include <iosfwd>

class Errors {
public:
  LG_Error* Err;
  LG_Error* TailErr;

  Errors(): Err(nullptr), TailErr(nullptr) {}
  ~Errors();

  void extend(LG_Error* newErr);
  void outputErrors(std::ostream& out, bool printFileName);
};