#include <scope/test.h>

#include "lightgrep_c_api.h"
#include "basic.h"

SCOPE_TEST(testDedupeOnDiffEncodings) {
  std::shared_ptr<ParserHandle> parser(lg_create_parser(0), lg_destroy_parser);
}
