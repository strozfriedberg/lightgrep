#include <scope/test.h>

#include "states.h"

SCOPE_TEST(litAccept) {
  LitState lit('a');
  char ch = 'a';
  SCOPE_ASSERT_EQUAL(&ch+1, lit.allowed(&ch, &ch+1));
  ch = 'b';
  SCOPE_ASSERT_EQUAL(&ch, lit.allowed(&ch, &ch+1));
}
