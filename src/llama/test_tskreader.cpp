#include <scope/test.h>

#include <cstring>
#include <stdexcept>

#include "tskreader.h"

#include "dummytsk.h"
#include "mockinputhandler.h"
#include "mockoutputhandler.h"

void noop_deleter(TSK_IMG_INFO*) {}

class FakeTskBase: public DummyTsk {
public:
  FakeTskBase() {
    std::memset(&img, 0, sizeof(img));
  }

  std::unique_ptr<TSK_IMG_INFO, void(*)(TSK_IMG_INFO*)> openImg(const char*) {
    return {&img, noop_deleter};
  }

  jsoncons::json convertImg(const TSK_IMG_INFO&) const {
    return jsoncons::json(jsoncons::json_object_arg);
  }

  jsoncons::json convertVS(const TSK_VS_INFO&) const {
    return jsoncons::json(
      jsoncons::json_object_arg,
      {
        { "volumes", jsoncons::json(jsoncons::json_array_arg) }
      }
    );
  }

  jsoncons::json convertVol(const TSK_VS_PART_INFO&) const {
    return jsoncons::json(jsoncons::json_object_arg);
  }

  jsoncons::json convertFS(const TSK_FS_INFO&) const {
    return jsoncons::json(jsoncons::json_object_arg);
  }

  jsoncons::json convertName(const TSK_FS_NAME&) const {
    return jsoncons::json(jsoncons::json_object_arg);
  }

  jsoncons::json convertMeta(const TSK_FS_META&, TimestampGetter&) const {
    return jsoncons::json(
      jsoncons::json_object_arg,
      {
        { "attrs", jsoncons::json(jsoncons::json_array_arg) }
      }
    );
  }

  jsoncons::json convertAttr(const TSK_FS_ATTR&) const {
    return jsoncons::json(jsoncons::json_object_arg);
  }

protected:
  TSK_IMG_INFO img;
};

class FakeTskWithVolumeSystem: public FakeTskBase {
public:
  bool walk(
    TSK_IMG_INFO* info,
    std::function<TSK_FILTER_ENUM(const TSK_VS_INFO*)> vs_cb,
    std::function<TSK_FILTER_ENUM(const TSK_VS_PART_INFO*)> vol_cb,
    std::function<TSK_FILTER_ENUM(TSK_FS_INFO*)> fs_cb,
    std::function<TSK_RETVAL_ENUM(TSK_FS_FILE*, const char*)>
  )
  {
    TSK_VS_INFO vs;
    std::memset(&vs, 0, sizeof(vs));
    vs_cb(&vs);

    TSK_VS_PART_INFO vol;
    std::memset(&vol, 0, sizeof(vol));

    TSK_FS_INFO fs;
    std::memset(&fs, 0, sizeof(fs));

    // first volume
    vol_cb(&vol);
    fs_cb(&fs);

    // second volume -- no filesystem!
    vol_cb(&vol);

    // third volume
    vol_cb(&vol);
    fs_cb(&fs);

    return true;
  }
};

SCOPE_TEST(testTskReaderVolumeSystem) {
  TskReader<FakeTskWithVolumeSystem> r("bogus.E01");

  auto ih = std::shared_ptr<MockInputHandler>(new MockInputHandler());
  r.setInputHandler(std::static_pointer_cast<InputHandler>(ih));

  auto oh = std::shared_ptr<MockOutputHandler>(new MockOutputHandler());
  r.setOutputHandler(std::static_pointer_cast<OutputHandler>(oh));

  SCOPE_ASSERT(r.open());
  SCOPE_ASSERT(r.startReading());

  SCOPE_ASSERT_EQUAL(1u, oh->Images.size());

  const jsoncons::json exp(
    jsoncons::json_object_arg,
    {
      {
        "volumeSystem",
        jsoncons::json(
          jsoncons::json_object_arg,
          {
            {
              "volumes",
              jsoncons::json(
                // volume 1
                jsoncons::json_array_arg,
                {
                  jsoncons::json(
                    jsoncons::json_object_arg,
                    {
                      {
                        "fileSystem",
                        jsoncons::json(jsoncons::json_object_arg)
                      }
                    }
                  ),
                  // volume 2
                  jsoncons::json(jsoncons::json_object_arg),
                  // volume 3
                  jsoncons::json(
                    jsoncons::json_object_arg,
                    {
                      {
                        "fileSystem",
                        jsoncons::json(jsoncons::json_object_arg)
                      }
                    }
                  )
                }
              )
            }
          }
        )
      }
    }
  );

  SCOPE_ASSERT_EQUAL(exp, oh->Images[0].Doc);

  SCOPE_ASSERT(oh->Dirents.empty());
  SCOPE_ASSERT(oh->Inodes.empty());
  SCOPE_ASSERT(ih->Batch.empty());
}

class FakeTskWithNoVolumeSystem: public FakeTskBase {
public:
  bool walk(
    TSK_IMG_INFO* info,
    std::function<TSK_FILTER_ENUM(const TSK_VS_INFO*)>,
    std::function<TSK_FILTER_ENUM(const TSK_VS_PART_INFO*)>,
    std::function<TSK_FILTER_ENUM(TSK_FS_INFO*)> fs_cb,
    std::function<TSK_RETVAL_ENUM(TSK_FS_FILE*, const char*)>
  )
  {
    TSK_FS_INFO fs;
    std::memset(&fs, 0, sizeof(fs));
    fs_cb(&fs);

    return true;
  }
};

SCOPE_TEST(testTskReaderNoVolumeSystem) {
  TskReader<FakeTskWithNoVolumeSystem> r("bogus.E01");

  auto ih = std::shared_ptr<MockInputHandler>(new MockInputHandler());
  r.setInputHandler(std::static_pointer_cast<InputHandler>(ih));

  auto oh = std::shared_ptr<MockOutputHandler>(new MockOutputHandler());
  r.setOutputHandler(std::static_pointer_cast<OutputHandler>(oh));

  SCOPE_ASSERT(r.open());
  SCOPE_ASSERT(r.startReading());

  SCOPE_ASSERT_EQUAL(1u, oh->Images.size());

  const jsoncons::json exp(
    jsoncons::json_object_arg,
    {
      {
        "fileSystem",
        jsoncons::json(jsoncons::json_object_arg)
      }
    }
  );

  SCOPE_ASSERT_EQUAL(exp, oh->Images[0].Doc);

  SCOPE_ASSERT(oh->Dirents.empty());
  SCOPE_ASSERT(oh->Inodes.empty());
  SCOPE_ASSERT(ih->Batch.empty());
}

class FakeTskWrongOrder: public FakeTskBase {
public:
  bool walk(
    TSK_IMG_INFO* info,
    std::function<TSK_FILTER_ENUM(const TSK_VS_INFO*)> vs_cb,
    std::function<TSK_FILTER_ENUM(const TSK_VS_PART_INFO*)> vol_cb,
    std::function<TSK_FILTER_ENUM(TSK_FS_INFO*)> fs_cb,
    std::function<TSK_RETVAL_ENUM(TSK_FS_FILE*, const char*)>
  )
  {
    TSK_VS_PART_INFO vol;
    std::memset(&vol, 0, sizeof(vol));

    // something is totally screwed up if we see a volume without seeing
    // a volume system containing it
    vol_cb(&vol);

    return true;
  }
};

// TODO: add more order tests
SCOPE_TEST(testTskReaderWrongOrder) {
  TskReader<FakeTskWithNoVolumeSystem> r("bogus.E01");

  auto ih = std::shared_ptr<MockInputHandler>(new MockInputHandler());
  r.setInputHandler(std::static_pointer_cast<InputHandler>(ih));

  auto oh = std::shared_ptr<MockOutputHandler>(new MockOutputHandler());
  r.setOutputHandler(std::static_pointer_cast<OutputHandler>(oh));

  SCOPE_ASSERT(r.open());
  SCOPE_EXPECT(r.startReading(), std::runtime_error);
}

/*
#include <cstring>


#include "filerecord.h"
#include "mockinputhandler.h"

SCOPE_TEST(testInodeDedupe) {
  TskReader reader("not_an_image.E01");

  reader.setInodeRange(0, 20);

  TSK_FS_ATTR attrRes;
  std::memset(&attrRes, 0, sizeof(attrRes));
  attrRes.flags = TSK_FS_ATTR_RES;
  attrRes.id = 1;
  attrRes.name = const_cast<char*>("$DATA");
  attrRes.name_size = 5;
  attrRes.next = nullptr;
  attrRes.rd.buf = (unsigned char*)("whatever");
  attrRes.rd.buf_size = 8;
  attrRes.rd.offset = 0;
  attrRes.size = 9;
  attrRes.type = TSK_FS_ATTR_TYPE_NTFS_DATA;

  TSK_FS_ATTRLIST alist;
  std::memset(&alist, 0, sizeof(alist));
  alist.head = &attrRes;

  TSK_FS_INFO fsInfo;
  std::memset(&fsInfo, 0, sizeof(fsInfo));
  fsInfo.ftype = TSK_FS_TYPE_NTFS;

  TSK_FS_META meta;
  std::memset(&meta, 0, sizeof(meta));
  meta.attr = &alist;
  meta.attr_state = TSK_FS_META_ATTR_STUDIED; // make TSK happy
  meta.link = const_cast<char*>("");

  TSK_FS_FILE myFile;
  std::memset(&myFile, 0, sizeof(myFile));
  myFile.meta = &meta;
  myFile.fs_info = &fsInfo;

  auto in = std::shared_ptr<MockInputHandler>(new MockInputHandler());
  reader.setInputHandler(std::static_pointer_cast<InputHandler>(in));

  meta.addr = 8;
  SCOPE_ASSERT(reader.addToBatch(&myFile));
  SCOPE_ASSERT_EQUAL(1u, in->batch.size());
  SCOPE_ASSERT_EQUAL(8u, in->batch.back().Doc["addr"]);

  meta.addr = 9;
  SCOPE_ASSERT(reader.addToBatch(&myFile));
  SCOPE_ASSERT_EQUAL(2u, in->batch.size());
  SCOPE_ASSERT_EQUAL(9u, in->batch.back().Doc["addr"]);

  meta.addr = 8; // dupe!
  SCOPE_ASSERT(!reader.addToBatch(&myFile));
  SCOPE_ASSERT_EQUAL(2u, in->batch.size());
}
*/
