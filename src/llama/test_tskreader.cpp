#include <scope/test.h>

#include <cstring>

#include "tskreader.h"

#include "filerecord.h"
#include "mockinputhandler.h"

SCOPE_TEST(testInodeDedupe) {
  TSKReader reader("not_an_image.E01");

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
