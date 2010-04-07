#include <scope/test.h>

#include "utility.h"

SCOPE_TEST(emptyFsm) {
  boost::shared_ptr<StaticFSM> tight(convert_to_static(DynamicFSM()));
}
