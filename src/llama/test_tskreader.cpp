#include <scope/test.h>

#include "tskreader.h"

#include "filerecord.h"

SCOPE_TEST(testInodeDedupe) {
  TSKReader reader("not_an_image.E01");

  reader.setInumRange(0, 20);

  TSK_FS_ATTR attrRes;
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
  alist.head = &attrRes;

  TSK_FS_INFO fsInfo;
  fsInfo.ftype = TSK_FS_TYPE_NTFS;

  TSK_FS_META meta;
  meta.attr = &alist;
  meta.link = const_cast<char*>("");

  TSK_FS_FILE myFile;
  myFile.meta = &meta;
  myFile.fs_info = &fsInfo;

  meta.addr = 8;
  std::vector<FileRecord> batch;
  SCOPE_ASSERT(reader.addToBatch(&myFile, batch));
  SCOPE_ASSERT_EQUAL(1u, batch.size());
  SCOPE_ASSERT_EQUAL(8u, batch.back().Doc["meta"]["addr"]);

  meta.addr = 9;
  SCOPE_ASSERT(reader.addToBatch(&myFile, batch));
  SCOPE_ASSERT_EQUAL(2u, batch.size());
  SCOPE_ASSERT_EQUAL(9u, batch.back().Doc["meta"]["addr"]);

  meta.addr = 8; // dupe!
  SCOPE_ASSERT(!reader.addToBatch(&myFile, batch));
  SCOPE_ASSERT_EQUAL(2u, batch.size());
}
