#include <scope/test.h>

#include <array>
#include <cstring>

#include "tskreaderhelper.h"

#include "dummytracker.h"
#include "dummytsk.h"

class FakeTsk: public DummyTsk {
public:
  jsoncons::json convertAttr(const TSK_FS_ATTR& attr) const {
    jsoncons::json ja(
      jsoncons::json_object_arg,
      {
        { "id", attr.id }
      }
    );

    if (attr.flags & TSK_FS_ATTR_NONRES) {
      ja["nrd_runs"] = jsoncons::json(jsoncons::json_array_arg);
    }

    return ja;
  }
};

/*
SCOPE_TEST(testHandleRunsNoSkipDataNoSlack) {
  TSK_FS_ATTR attr;
  std::memset(&attr, 0, sizeof(attr));

  

  TskReaderHelper::handleRuns( );

}
*/

SCOPE_TEST(testHandleAttrs) {
  std::array<TSK_FS_ATTR, 5> attr;
  std::memset(&attr, 0, sizeof(attr));

  // link up the attrs
  for (size_t i = 0; i < attr.size() - 1; ++i) {
    attr[i].id = i;
    attr[i].next = &attr[i+1];
  }

  // set some flags
  attr[0].flags = static_cast<TSK_FS_ATTR_FLAG_ENUM>(TSK_FS_ATTR_INUSE | TSK_FS_ATTR_RES);
  attr[1].flags = static_cast<TSK_FS_ATTR_FLAG_ENUM>(TSK_FS_ATTR_INUSE | TSK_FS_ATTR_NONRES);
  attr[2].flags = TSK_FS_ATTR_FLAG_NONE;
  attr[3].flags =  static_cast<TSK_FS_ATTR_FLAG_ENUM>(TSK_FS_ATTR_INUSE | TSK_FS_ATTR_NONRES);
  attr[4].flags = TSK_FS_ATTR_FLAG_NONE;

  // attach the attrs to a meta
  TSK_FS_ATTRLIST alist;
  std::memset(&alist, 0, sizeof(alist));
  alist.head = &attr[0];

  TSK_FS_META meta;
  std::memset(&meta, 0, sizeof(meta));
  meta.attr = &alist;

  // handle the attrs
  FakeTsk tsk;
  DummyTracker tracker;
  jsoncons::json jattrs(jsoncons::json_array_arg);
  TskReaderHelper::handleAttrs(meta, 0, 3, 42, tsk, tracker, jattrs);

  // attrs 2, 4 are omitted because they're not in use
  const jsoncons::json exp(
    jsoncons::json_array_arg,
    {
      jsoncons::json(
        jsoncons::json_object_arg,
        {
          { "id", 0 }
        }
      ),
      jsoncons::json(
        jsoncons::json_object_arg,
        {
          { "id", 1 },
          {
            "nrd_runs",
            jsoncons::json(jsoncons::json_array_arg)
          }
        }
      ),
      jsoncons::json(
        jsoncons::json_object_arg,
        {
          { "id", 3 },
          {
            "nrd_runs",
            jsoncons::json(jsoncons::json_array_arg)
          }
        }
      )
    }
  );

  SCOPE_ASSERT_EQUAL(exp, jattrs);
}
