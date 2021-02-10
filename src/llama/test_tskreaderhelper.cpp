#include <scope/test.h>

#include <array>
#include <cstring>

#include "tskreaderhelper.h"

#include "dummytracker.h"
#include "dummytsk.h"

class FakeHandleAttrsTsk: public DummyTsk {
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

SCOPE_TEST(testHandleAttrs) {
  std::array<TSK_FS_ATTR, 5> attr;
  std::memset(&attr, 0, sizeof(attr));

  // link up the attrs
  for (size_t i = 0; i < attr.size() - 1; ++i) {
    attr[i].id = i;
    attr[i].next = &attr[i+1];
  }

  const TSK_FS_ATTR_FLAG_ENUM res = static_cast<TSK_FS_ATTR_FLAG_ENUM>(TSK_FS_ATTR_INUSE | TSK_FS_ATTR_RES);
  const TSK_FS_ATTR_FLAG_ENUM nonres = static_cast<TSK_FS_ATTR_FLAG_ENUM>(TSK_FS_ATTR_INUSE | TSK_FS_ATTR_NONRES);

  // set some flags
  attr[0].flags = res;
  attr[1].flags = nonres;
  attr[2].flags = TSK_FS_ATTR_FLAG_NONE;
  attr[3].flags = nonres;
  attr[4].flags = TSK_FS_ATTR_FLAG_NONE;

  // attach the attrs to a meta
  TSK_FS_ATTRLIST alist;
  std::memset(&alist, 0, sizeof(alist));
  alist.head = &attr[0];

  TSK_FS_META meta;
  std::memset(&meta, 0, sizeof(meta));
  meta.attr = &alist;

  // handle the attrs
  FakeHandleAttrsTsk tsk;
  DummyTracker tracker;
  jsoncons::json jattrs(jsoncons::json_array_arg);
  TskReaderHelper::handleAttrs(meta, 0, 3, 42, tsk, tracker, jattrs);

  // attrs 2, 4 should be omitted because they're not in use
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

class FakeHandleRunsTsk: public DummyTsk {
public:
  jsoncons::json convertRun(const TSK_FS_ATTR_RUN& run) const {
    return jsoncons::json(
      jsoncons::json_object_arg,
      {
        { "addr", run.addr }
      }
    ); 
  }
};

SCOPE_TEST(testHandleRunsNoSkipDataNoSlack) {
  const uint64_t fsOffset = 12;
  const uint64_t blockSize = 3;
  const uint64_t inum = 42;

  TSK_FS_ATTR attr;
  std::memset(&attr, 0, sizeof(attr));

  std::array<TSK_FS_ATTR_RUN, 5> run;
  std::memset(&run, 0, sizeof(run));

  for (size_t i = 0; i < run.size() - 1; ++i) {
    run[i].next = &run[i+1]; 
  } 
  attr.nrd.run = &run[0];
  attr.nrd.run_end = &run[4];
  attr.nrd.skiplen = 0;
  attr.nrd.allocsize = 9030;
  attr.nrd.initsize = 9030;

  run[0].offset = 3;
  run[0].addr = 81;
  run[0].len = 5;
  run[0].flags = TSK_FS_ATTR_RUN_FLAG_NONE;

  run[1].offset = 8;
  run[1].addr = 96;
  run[1].len = 1;
  run[1].flags = TSK_FS_ATTR_RUN_FLAG_NONE;

  run[2].offset = 9;
  run[2].addr = 1234;
  run[2].len = 3000;
  run[2].flags = TSK_FS_ATTR_RUN_FLAG_NONE;

  run[3].offset = 3009;
  run[3].addr = 2;
  run[3].len = 7;
  run[3].flags = TSK_FS_ATTR_RUN_FLAG_NONE;

  run[4].offset = 3009;
  run[4].addr = 8;
  run[4].len = 1;
  run[4].flags = TSK_FS_ATTR_RUN_FLAG_NONE;

  FakeHandleRunsTsk tsk;
  std::unique_ptr<InodeAndBlockTracker> tracker(new DummyTracker());
  jsoncons::json jnrd_runs(jsoncons::json_array_arg);
  TskReaderHelper::handleRuns(
    attr, fsOffset, blockSize, inum, tsk, *tracker,
    &InodeAndBlockTracker::markBlocksAllocated, jnrd_runs
  );

  const jsoncons::json exp(
    jsoncons::json_array_arg,
    {
      jsoncons::json(
        jsoncons::json_object_arg,
        {
          { "addr", 81 }
        }
      ),
      jsoncons::json(
        jsoncons::json_object_arg,
        {
          { "addr", 96 }
        }
      ),
      jsoncons::json(
        jsoncons::json_object_arg,
        {
          { "addr", 1234 }
        }
      ),
      jsoncons::json(
        jsoncons::json_object_arg,
        {
          { "addr", 2 }
        }
      ),
      jsoncons::json(
        jsoncons::json_object_arg,
        {
          { "addr", 8 }
        }
      ),
    }
  );

  SCOPE_ASSERT_EQUAL(exp, jnrd_runs);
}
