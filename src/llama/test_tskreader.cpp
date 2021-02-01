#include <scope/test.h>

#include "tskreader.h"

class FakeTskWrapper {
public:
  std::unique_ptr<TSK_IMG_INFO, void(*)(TSK_IMG_INFO*)> openImg(const char* path) const {
    return {nullptr, nullptr};
  }

  std::unique_ptr<TSK_FS_INFO, void(*)(TSK_FS_INFO*)> openFS(TSK_IMG_INFO* img, TSK_OFF_T off, TSK_FS_TYPE_ENUM type) const {
    return {nullptr, nullptr};
  }

  std::unique_ptr<TSK_FS_FILE, void(*)(TSK_FS_FILE*)> openFile(TSK_FS_INFO* fs, TSK_INUM_T inum) const {
    return {nullptr, nullptr};
  }

  void populateAttrs(TSK_FS_FILE* file) const {
  }
};

class FakeTskWalker {
public:
  bool walk(
    TSK_IMG_INFO* info,
    std::function<TSK_FILTER_ENUM(const TSK_VS_INFO*)> vs_cb,
    std::function<TSK_FILTER_ENUM(const TSK_VS_PART_INFO*)> vol_cb,
    std::function<TSK_FILTER_ENUM(TSK_FS_INFO*)> fs_cb,
    std::function<TSK_RETVAL_ENUM(TSK_FS_FILE*, const char*)> file_cb
  )
  {
    return false;
  }
};

SCOPE_TEST(testMakeTskReader) {
  TskReader<FakeTskWrapper, FakeTskWalker>("bogus.E01");
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
