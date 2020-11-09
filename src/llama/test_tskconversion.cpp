#include <scope/test.h>

#include "tskconversion.h"

SCOPE_TEST(testTskVolumeSystemType) {
  TskConverter   munge;
  SCOPE_ASSERT_EQUAL("Unknown", munge.volumeSystemType(0));
  SCOPE_ASSERT_EQUAL("MBR", munge.volumeSystemType(1));
  SCOPE_ASSERT_EQUAL("BSD", munge.volumeSystemType(2));
  SCOPE_ASSERT_EQUAL("Sun", munge.volumeSystemType(4));
  SCOPE_ASSERT_EQUAL("Macintosh", munge.volumeSystemType(8));
  SCOPE_ASSERT_EQUAL("GPT", munge.volumeSystemType(16));
  SCOPE_ASSERT_EQUAL("Unknown", munge.volumeSystemType(0xffff));
}

SCOPE_TEST(testTskVolumeFlags) {
  TskConverter   munge;
  SCOPE_ASSERT_EQUAL("", munge.volumeFlags(0));
  SCOPE_ASSERT_EQUAL("Allocated", munge.volumeFlags(1));
  SCOPE_ASSERT_EQUAL("Unallocated", munge.volumeFlags(2));
  SCOPE_ASSERT_EQUAL("", munge.volumeFlags(3));
  SCOPE_ASSERT_EQUAL("Volume System", munge.volumeFlags(4));
  SCOPE_ASSERT_EQUAL("", munge.volumeFlags(5));
  // I don't think there's much point in testing for that "ALL" enum
}

SCOPE_TEST(testTskFilesystemFlags) {
  TskConverter   munge;
  SCOPE_ASSERT_EQUAL("", munge.filesystemFlags(0));
  SCOPE_ASSERT_EQUAL("Sequenced", munge.filesystemFlags(1));
  SCOPE_ASSERT_EQUAL("Nanosecond precision", munge.filesystemFlags(2));
  SCOPE_ASSERT_EQUAL("Sequenced, Nanosecond precision", munge.filesystemFlags(3));
}

SCOPE_TEST(testTskNameTypeLookup) {
  TskConverter   munge;
  SCOPE_ASSERT_EQUAL("Undefined", munge.nameType(0));
  SCOPE_ASSERT_EQUAL("Named Pipe", munge.nameType(1));
  SCOPE_ASSERT_EQUAL("Character Device", munge.nameType(2));
  SCOPE_ASSERT_EQUAL("Folder", munge.nameType(3));
  SCOPE_ASSERT_EQUAL("Block Device", munge.nameType(4));
  SCOPE_ASSERT_EQUAL("File", munge.nameType(5));
  SCOPE_ASSERT_EQUAL("Symbolic Link", munge.nameType(6));
  SCOPE_ASSERT_EQUAL("Domain Socket", munge.nameType(7));
  SCOPE_ASSERT_EQUAL("Shadow Inode", munge.nameType(8));
  SCOPE_ASSERT_EQUAL("Whiteout Inode", munge.nameType(9));
  SCOPE_ASSERT_EQUAL("Virtual", munge.nameType(10));
  SCOPE_ASSERT_EQUAL("Virtual Folder", munge.nameType(11));
  SCOPE_ASSERT_EQUAL("Undefined", munge.nameType(12));
}

SCOPE_TEST(testTskNameFlags) {
  TskConverter   munge;
  SCOPE_ASSERT_EQUAL("Allocated", munge.nameFlags(1));
  SCOPE_ASSERT_EQUAL("Deleted", munge.nameFlags(2));
}

// Seriously, same shit as name type, different order
SCOPE_TEST(testTskMetaTypeLookup) {
  TskConverter   munge;
  SCOPE_ASSERT_EQUAL("Undefined", munge.metaType(0));
  SCOPE_ASSERT_EQUAL("File", munge.metaType(1));
  SCOPE_ASSERT_EQUAL("Folder", munge.metaType(2));
  SCOPE_ASSERT_EQUAL("Named Pipe", munge.metaType(3));
  SCOPE_ASSERT_EQUAL("Character Device", munge.metaType(4));
  SCOPE_ASSERT_EQUAL("Block Device", munge.metaType(5));
  SCOPE_ASSERT_EQUAL("Symbolic Link", munge.metaType(6));
  SCOPE_ASSERT_EQUAL("Shadow Inode", munge.metaType(7));
  SCOPE_ASSERT_EQUAL("Domain Socket", munge.metaType(8));
  SCOPE_ASSERT_EQUAL("Whiteout Inode", munge.metaType(9));
  SCOPE_ASSERT_EQUAL("Virtual", munge.metaType(10));
  SCOPE_ASSERT_EQUAL("Virtual Folder", munge.metaType(11));
  SCOPE_ASSERT_EQUAL("Undefined", munge.metaType(12));
}

SCOPE_TEST(testTskMetaFlags) {
  TskConverter   munge;
  SCOPE_ASSERT_EQUAL("Allocated", munge.metaFlags(1));
  SCOPE_ASSERT_EQUAL("Deleted", munge.metaFlags(2));
  SCOPE_ASSERT_EQUAL("Used", munge.metaFlags(4));
  SCOPE_ASSERT_EQUAL("Unused", munge.metaFlags(8));
  SCOPE_ASSERT_EQUAL("Compressed", munge.metaFlags(16));
  SCOPE_ASSERT_EQUAL("Orphan", munge.metaFlags(32));
  SCOPE_ASSERT_EQUAL("Deleted, Used", munge.metaFlags(6));
}

SCOPE_TEST(testTskAttrType) {
  TskConverter   munge;
  SCOPE_ASSERT_EQUAL("Unknown", munge.attrType(TSK_FS_ATTR_TYPE_NOT_FOUND));
  SCOPE_ASSERT_EQUAL("Data", munge.attrType(TSK_FS_ATTR_TYPE_DEFAULT)); // default _is_ data, so match up with NTFS Data
  SCOPE_ASSERT_EQUAL("Standard Information", munge.attrType(TSK_FS_ATTR_TYPE_NTFS_SI));
  SCOPE_ASSERT_EQUAL("NTFS Attributes", munge.attrType(TSK_FS_ATTR_TYPE_NTFS_ATTRLIST));
  SCOPE_ASSERT_EQUAL("Filename", munge.attrType(TSK_FS_ATTR_TYPE_NTFS_FNAME));
  SCOPE_ASSERT_EQUAL("ObjID", munge.attrType(TSK_FS_ATTR_TYPE_NTFS_OBJID));
  SCOPE_ASSERT_EQUAL("Sec", munge.attrType(TSK_FS_ATTR_TYPE_NTFS_SEC));
  SCOPE_ASSERT_EQUAL("VName", munge.attrType(TSK_FS_ATTR_TYPE_NTFS_VNAME));
  SCOPE_ASSERT_EQUAL("VInfo", munge.attrType(TSK_FS_ATTR_TYPE_NTFS_VINFO));
  SCOPE_ASSERT_EQUAL("Data", munge.attrType(TSK_FS_ATTR_TYPE_NTFS_DATA));
  SCOPE_ASSERT_EQUAL("IdxRoot", munge.attrType(TSK_FS_ATTR_TYPE_NTFS_IDXROOT));
  SCOPE_ASSERT_EQUAL("IdxAlloc", munge.attrType(TSK_FS_ATTR_TYPE_NTFS_IDXALLOC));
  SCOPE_ASSERT_EQUAL("Bitmap", munge.attrType(TSK_FS_ATTR_TYPE_NTFS_BITMAP));
  SCOPE_ASSERT_EQUAL("Symlink", munge.attrType(TSK_FS_ATTR_TYPE_NTFS_SYMLNK));

  // It would be great if this would return Reparse, but it can't because
  // reparse has the same typecode as symlink. So instead we assert the
  // broken behavior. This was a change from Win2K and WinXP.
  SCOPE_ASSERT_EQUAL("Symlink", munge.attrType(TSK_FS_ATTR_TYPE_NTFS_REPARSE));

  SCOPE_ASSERT_EQUAL("EAInfo", munge.attrType(TSK_FS_ATTR_TYPE_NTFS_EAINFO));
  SCOPE_ASSERT_EQUAL("EA", munge.attrType(TSK_FS_ATTR_TYPE_NTFS_EA));
  SCOPE_ASSERT_EQUAL("Prop", munge.attrType(TSK_FS_ATTR_TYPE_NTFS_PROP));
  SCOPE_ASSERT_EQUAL("Log", munge.attrType(TSK_FS_ATTR_TYPE_NTFS_LOG));

  SCOPE_ASSERT_EQUAL("Indirect", munge.attrType(TSK_FS_ATTR_TYPE_UNIX_INDIR));
  SCOPE_ASSERT_EQUAL("Extents", munge.attrType(TSK_FS_ATTR_TYPE_UNIX_EXTENT));

  // Types for HFS+ File Attributes
  SCOPE_ASSERT_EQUAL("Data", munge.attrType(TSK_FS_ATTR_TYPE_HFS_DEFAULT));
  SCOPE_ASSERT_EQUAL("Data", munge.attrType(TSK_FS_ATTR_TYPE_HFS_DATA));
  SCOPE_ASSERT_EQUAL("Resource", munge.attrType(TSK_FS_ATTR_TYPE_HFS_RSRC));
  SCOPE_ASSERT_EQUAL("EA", munge.attrType(TSK_FS_ATTR_TYPE_HFS_EXT_ATTR));
  SCOPE_ASSERT_EQUAL("Compressed", munge.attrType(TSK_FS_ATTR_TYPE_HFS_COMP_REC));
}

SCOPE_TEST(testTskAttrFlags) {
  TskConverter   munge;
  SCOPE_ASSERT_EQUAL("", munge.attrFlags(0));
  SCOPE_ASSERT_EQUAL("In Use", munge.attrFlags(1));
  SCOPE_ASSERT_EQUAL("Non-resident", munge.attrFlags(2));
  SCOPE_ASSERT_EQUAL("Resident", munge.attrFlags(4));
  SCOPE_ASSERT_EQUAL("Encrypted", munge.attrFlags(16));
  SCOPE_ASSERT_EQUAL("Compressed", munge.attrFlags(32));
  SCOPE_ASSERT_EQUAL("Sparse", munge.attrFlags(64));
  SCOPE_ASSERT_EQUAL("Recovered", munge.attrFlags(128));
  SCOPE_ASSERT_EQUAL("In Use, Non-resident", munge.attrFlags(3));
}

SCOPE_TEST(testTskNrdRunFlags) {
  TskConverter   munge;
  SCOPE_ASSERT_EQUAL("", munge.nrdRunFlags(TSK_FS_ATTR_RUN_FLAG_NONE));
  SCOPE_ASSERT_EQUAL("Filler", munge.nrdRunFlags(TSK_FS_ATTR_RUN_FLAG_FILLER));
  SCOPE_ASSERT_EQUAL("Sparse", munge.nrdRunFlags(TSK_FS_ATTR_RUN_FLAG_SPARSE));
}

SCOPE_TEST(testTskConvertHexEncode) {
  TskConverter munge;
  unsigned char s1[] = {0xFF},
                s2[] = {0x1c, 0x2d},
                s3[] = {0x0f, 0xf0, 0x02},
                s4[] = {0x00, 0x00, 0x00, 0x00},
                s5[] = {0xE2, 0x49, 0x49, 0x32, 0xCF, 0x01, 0x9D, 0xC8, 0x40, 0x57, 0xF6, 0x48, 0x78, 0x92, 0x6D},
                s6[] = {0xAE, 0xED, 0x3A, 0xC7, 0x39, 0xD8, 0xFD, 0xDF, 0xCB, 0xD1, 0x91, 0x3B, 0x9E, 0x91, 0xE4};

  SCOPE_ASSERT_EQUAL("ff", munge.hexEncode(s1, 1));
  SCOPE_ASSERT_EQUAL("1c2d", munge.hexEncode(s2, 2));
  SCOPE_ASSERT_EQUAL("0ff002", munge.hexEncode(s3, 3));
  SCOPE_ASSERT_EQUAL("00000000", munge.hexEncode(s4, 4));
  SCOPE_ASSERT_EQUAL("e2494932cf019dc84057f64878926d", munge.hexEncode(s5, 15));
  SCOPE_ASSERT_EQUAL("aeed3ac739d8fddfcbd1913b9e91e4", munge.hexEncode(s6, 15));
}

SCOPE_TEST(testTskConvertNRDs) {
  TSK_FS_ATTR_RUN nrd;
  nrd.addr   = 15;
  nrd.len    = 3045;
  nrd.offset = 17;
  nrd.flags  = TSK_FS_ATTR_RUN_FLAG_SPARSE;

  TskConverter munge;
  const jsoncons::json js = munge.convertNRDR(nrd);
  const std::string expected = "{\"addr\":15,\"flags\":\"Sparse\",\"len\":3045,\"offset\":17}";
  const std::string actual = js.as<std::string>();
  SCOPE_ASSERT_EQUAL(expected, actual);
}

TSK_FS_ATTR* setResAttr(TSK_FS_ATTR& attr) {
  attr.flags = static_cast<TSK_FS_ATTR_FLAG_ENUM>(TSK_FS_ATTR_RES | TSK_FS_ATTR_INUSE);
  attr.id = 1;
  attr.name = const_cast<char*>("$DATA\0 3.1459"); // will be clipped at null character
  attr.name_size = 13;
  attr.next = nullptr;
  attr.rd.buf = (unsigned char*)("whatever\tslack");
  attr.rd.buf_size = 14;
  attr.rd.offset = 0;
  attr.size = 8;
  attr.type = TSK_FS_ATTR_TYPE_NTFS_DATA;
  return &attr;
}

SCOPE_TEST(testTskConvertAttrRes) {
  TSK_FS_ATTR attr;
  setResAttr(attr);

  TskConverter munge;
  const jsoncons::json js = munge.convertAttr(attr);
  SCOPE_ASSERT_EQUAL(1, js["id"]);
  SCOPE_ASSERT_EQUAL("In Use, Resident", js["flags"]);
  SCOPE_ASSERT_EQUAL("$DATA", js["name"]);
  SCOPE_ASSERT_EQUAL("7768617465766572", js["rd_buf"]);
  SCOPE_ASSERT_EQUAL(0, js["rd_offset"]);
  SCOPE_ASSERT_EQUAL(8u, js["size"]);
  SCOPE_ASSERT_EQUAL("Data", js["type"]);
}

TSK_FS_ATTR* setNonresAttr(TSK_FS_ATTR& attr, TSK_FS_ATTR_RUN& nrd1, TSK_FS_ATTR_RUN& nrd2) {
  nrd1.addr = 12;
  nrd1.flags = TSK_FS_ATTR_RUN_FLAG_NONE;
  nrd1.len = 2;
  nrd1.offset = 0;
  nrd1.next = &nrd2;

  nrd2.addr = 38;
  nrd2.flags = TSK_FS_ATTR_RUN_FLAG_NONE;
  nrd2.len = 1;
  nrd2.offset = 2;
  nrd2.next = nullptr;

  attr.flags = (TSK_FS_ATTR_FLAG_ENUM)(TSK_FS_ATTR_NONRES | TSK_FS_ATTR_INUSE);
  attr.id = 4;
  attr.name = const_cast<char*>("$DATA");
  attr.name_size = 5;
  attr.next = nullptr;
  // Set up the nrds
  attr.nrd.run = &nrd1;
  attr.nrd.run_end = &nrd2;
  attr.nrd.allocsize = 1536;
  // The following aren't values we'd expect to see, but test serialization well enough
  attr.nrd.compsize = 3;
  attr.nrd.initsize = 6;
  attr.nrd.skiplen = 9;
  // These should be ignored due to flags
  attr.rd.buf = (unsigned char*)("whatever");
  attr.rd.buf_size = 8;
  attr.rd.offset = 5;

  attr.size = 1235;
  attr.type = TSK_FS_ATTR_TYPE_NTFS_DATA;
  return &attr;
}

void testNonresAttr(const jsoncons::json& js) {
  SCOPE_ASSERT_EQUAL(4, js["id"]);
  SCOPE_ASSERT_EQUAL("In Use, Non-resident", js["flags"]);
  SCOPE_ASSERT_EQUAL("$DATA", js["name"]);

  SCOPE_ASSERT(!js.contains("rd_buf"));
  SCOPE_ASSERT(!js.contains("rd_offset"));
  SCOPE_ASSERT_EQUAL(2u, js["nrd_runs"].size());
  SCOPE_ASSERT_EQUAL(12, js["nrd_runs"][0]["addr"]);
  SCOPE_ASSERT_EQUAL(38, js["nrd_runs"][1]["addr"]);
  SCOPE_ASSERT_EQUAL(1536, js["nrd_allocsize"]);
  SCOPE_ASSERT_EQUAL(3, js["nrd_compsize"]);
  SCOPE_ASSERT_EQUAL(6, js["nrd_initsize"]);
  SCOPE_ASSERT_EQUAL(9, js["nrd_skiplen"]);

  SCOPE_ASSERT_EQUAL(1235u, js["size"]);
  SCOPE_ASSERT_EQUAL("Data", js["type"]);
}

SCOPE_TEST(testTskConvertAttrNonRes) {
  TSK_FS_ATTR_RUN nrd1,
                  nrd2;

  TSK_FS_ATTR attr;
  setNonresAttr(attr, nrd1, nrd2);

  TskConverter munge;
  const jsoncons::json js = munge.convertAttr(attr);
  testNonresAttr(js);
}

SCOPE_TEST(testTskMetaConvert) {
  const TSK_FS_TYPE_ENUM fstype = TSK_FS_TYPE_DETECT; // whatever

  TSK_FS_ATTR_RUN nrd1,
                  nrd2;

  TSK_FS_ATTR attrNonRes;
  std::memset(&attrNonRes, 0, sizeof(attrNonRes));

  TSK_FS_ATTR attrRes;
  std::memset(&attrRes, 0, sizeof(attrRes));

  TSK_FS_ATTRLIST alist;
  std::memset(&alist, 0, sizeof(alist));

  TSK_FS_META meta;
  std::memset(&meta, 0, sizeof(meta));

  meta.addr = 17;
  meta.flags = TSK_FS_META_FLAG_UNALLOC;
  meta.type = TSK_FS_META_TYPE_REG;

  meta.uid = 21;
  meta.gid = 1026;

  meta.link = const_cast<char*>("I_am_the_target"); // terrible that there's no link_size
  meta.nlink = 2;
  meta.seq = 8;

  meta.attr = &alist;
  alist.head = setNonresAttr(attrNonRes, nrd1, nrd2);
  attrNonRes.next = setResAttr(attrRes);

  // the attr_state enum is dumb
  // we have to set the state to studied, but not worth reporting
  meta.attr_state = TSK_FS_META_ATTR_STUDIED;

  meta.atime = 1578364822; // 2020-01-07 02:40:22
  meta.atime_nano = 123456700;
  meta.crtime = 31337;     // 1970-01-01 08:42:17
  meta.crtime_nano = 123456400;
  meta.ctime = 234123870;  // 1977-06-02 18:24:30
  meta.ctime_nano = 315227845;
  meta.mtime = 314159265;  // 1979-12-16 02:27:45
  meta.mtime_nano = 999999999;

  // meta.name2 = "SHRTNM~2";

  TskConverter munge;
  jsoncons::json js = munge.convertMeta(meta, fstype);

  SCOPE_ASSERT_EQUAL(17, js["addr"]);
  SCOPE_ASSERT_EQUAL("Deleted", js["flags"]);
  SCOPE_ASSERT_EQUAL("File", js["type"]);

  SCOPE_ASSERT_EQUAL("21", js["uid"]); // stringized
  SCOPE_ASSERT_EQUAL("1026", js["gid"]); // also stringized

  SCOPE_ASSERT_EQUAL("I_am_the_target", js["link"]);
  SCOPE_ASSERT_EQUAL(2, js["nlink"]);
  SCOPE_ASSERT_EQUAL(8, js["seq"]);
  // SCOPE_ASSERT_EQUAL("SHRTNM~2", js["name2"]);

  SCOPE_ASSERT_EQUAL(2u, js["attrs"].size());
  SCOPE_ASSERT_EQUAL(4, js["attrs"][0]["id"]);
  SCOPE_ASSERT_EQUAL(1, js["attrs"][1]["id"]);

  // basic four are good
  SCOPE_ASSERT_EQUAL("2020-01-07 02:40:22.1234567", js.at("accessed"));
  SCOPE_ASSERT_EQUAL("1970-01-01 08:42:17.1234564", js.at("created"));
  SCOPE_ASSERT_EQUAL("1977-06-02 18:24:30.315227845", js.at("metadata"));
  SCOPE_ASSERT_EQUAL("1979-12-16 02:27:45.999999999", js.at("modified"));
  // others not so much
  SCOPE_ASSERT(js.at("deleted").is_null());
  SCOPE_ASSERT(js.at("backup").is_null());
  SCOPE_ASSERT(js.at("fn_accessed").is_null());
  SCOPE_ASSERT(js.at("fn_created").is_null());
  SCOPE_ASSERT(js.at("fn_metadata").is_null());
  SCOPE_ASSERT(js.at("fn_modified").is_null());

  meta.link = nullptr;
  js = munge.convertMeta(meta, fstype);
  SCOPE_ASSERT_EQUAL("", js["link"]);
}

SCOPE_TEST(testTskNameConvert) {
  TSK_FS_NAME name;

  name.name = const_cast<char*>("woowoowoo\0bad bad bad");
  name.name_size = 9;
  name.shrt_name = const_cast<char*>("WOOWOO~1");
  name.shrt_name_size = 8;
  name.meta_addr = 7;
  name.meta_seq = 6;
  name.par_addr = 231;
  name.par_seq = 72;
  name.type = TSK_FS_NAME_TYPE_SOCK;
  name.flags = TSK_FS_NAME_FLAG_ALLOC;

  TskConverter munge;
  const jsoncons::json js = munge.convertName(name);

  SCOPE_ASSERT_EQUAL("woowoowoo", js["name"]);
  SCOPE_ASSERT_EQUAL("WOOWOO~1", js["shrt_name"]);
  SCOPE_ASSERT_EQUAL(7, js["meta_addr"]);
  SCOPE_ASSERT_EQUAL(6, js["meta_seq"]);
  SCOPE_ASSERT_EQUAL(231, js["par_addr"]);
  SCOPE_ASSERT_EQUAL(72, js["par_seq"]);
  SCOPE_ASSERT_EQUAL("Domain Socket", js["type"]);
  SCOPE_ASSERT_EQUAL("Allocated", js["flags"]);
}

SCOPE_TEST(testTskConvertTimestamps) {
  TSK_FS_META meta;
  meta.atime = 1578364822; // 2020-01-07 02:40:22
  meta.atime_nano = 123456700;
  meta.crtime = 31337; // 1970-01-01 08:42:17
  meta.crtime_nano = 123456400;
  meta.ctime = 234123870; // 1977-06-02 18:24:30
  meta.ctime_nano = 315227845;
  meta.mtime = 314159265; // 1979-12-16 02:27:45
  meta.mtime_nano = 999999999;

  jsoncons::json ts;

  TskConverter munge;
  munge.convertTimestamps(meta, TSK_FS_TYPE_DETECT, ts);
}

SCOPE_TEST(testTskConvertEpochBeginningIsNull) {
  TSK_FS_META meta;
  meta.atime = 0; // 1970-01-01 00:00:00
  meta.atime_nano = 0;
  meta.crtime = 1; // 1970-01-01 00:00::01
  meta.crtime_nano = 0;
  meta.ctime = 0; // 1970-01-01 00:00:00.000000001
  meta.ctime_nano = 1;
  meta.mtime = 0; // 1970-01-01 00:00:00
  meta.mtime_nano = 0;

  jsoncons::json ts;

  TskConverter munge;
  munge.convertTimestamps(meta, TSK_FS_TYPE_DETECT, ts);
  // basic four are good
  SCOPE_ASSERT(ts.at("accessed").is_null());
  SCOPE_ASSERT_EQUAL("1970-01-01 00:00:01", ts.at("created"));
  SCOPE_ASSERT_EQUAL("1970-01-01 00:00:00.000000001", ts.at("metadata"));
  SCOPE_ASSERT(ts.at("modified").is_null());
}

SCOPE_TEST(testTskConvertNTFSTimestamps) {
  TSK_FS_META meta;
  meta.atime = 1578364822; // 2020-01-07 02:40:22
  meta.atime_nano = 123456700;
  meta.crtime = 31337; // 1970-01-01 08:42:17
  meta.crtime_nano = 123456400;
  meta.ctime = 234123870; // 1977-06-02 18:24:30
  meta.ctime_nano = 315227845;
  meta.mtime = 314159265; // 1979-12-16 02:27:45
  meta.mtime_nano = 999999999;

  meta.time2.ntfs.fn_atime = 1578602384; // 2020-01-09 20:39:44
  meta.time2.ntfs.fn_atime_nano = 1000;
  meta.time2.ntfs.fn_crtime = 1425542407; // 2015-03-05 08:00:07
  meta.time2.ntfs.fn_crtime_nano = 0;
  meta.time2.ntfs.fn_ctime = 1371346223; // 2013-06-16 01:30:23
  meta.time2.ntfs.fn_ctime_nano = 900000000;
  meta.time2.ntfs.fn_mtime = 1123946859; // 2005-08-13 15:27:39
  meta.time2.ntfs.fn_mtime_nano = 1001001;

  jsoncons::json ts;

  TskConverter munge;
  munge.convertTimestamps(meta, TSK_FS_TYPE_NTFS, ts);
  // basic four are good
  SCOPE_ASSERT_EQUAL("2020-01-07 02:40:22.1234567", ts.at("accessed"), "accessed");
  SCOPE_ASSERT_EQUAL("1970-01-01 08:42:17.1234564", ts.at("created"), "created");
  SCOPE_ASSERT_EQUAL("1977-06-02 18:24:30.315227845", ts.at("metadata"), "metadata");
  SCOPE_ASSERT_EQUAL("1979-12-16 02:27:45.999999999", ts.at("modified"), "modified");
  // and filename attr timestamps
  SCOPE_ASSERT_EQUAL("2020-01-09 20:39:44.000001", ts.at("fn_accessed"), "fn_accessed");
  SCOPE_ASSERT_EQUAL("2015-03-05 08:00:07", ts.at("fn_created"), "fn_created");
  SCOPE_ASSERT_EQUAL("2013-06-16 01:30:23.9", ts.at("fn_metadata"), "fn_metadata");
  SCOPE_ASSERT_EQUAL("2005-08-13 15:27:39.001001001", ts.at("fn_modified"), "fn_modified");
  // not these
  SCOPE_ASSERT(ts.at("deleted").is_null());
  SCOPE_ASSERT(ts.at("backup").is_null());
}

SCOPE_TEST(testTskConvertMacTimestamps) {
  TSK_FS_META meta;
  meta.atime = 1578364822; // 2020-01-07 02:40:22
  meta.atime_nano = 123456700;
  meta.crtime = 31337; // 1970-01-01 08:42:17
  meta.crtime_nano = 123456400;
  meta.ctime = 234123870; // 1977-06-02 18:24:30
  meta.ctime_nano = 315227845;
  meta.mtime = 314159265; // 1979-12-16 02:27:45
  meta.mtime_nano = 999999999;

  meta.time2.hfs.bkup_time = 1578602384; // 2020-01-09 20:39:44
  meta.time2.hfs.bkup_time_nano = 1000;

  jsoncons::json ts;

  TskConverter munge;
  munge.convertTimestamps(meta, TSK_FS_TYPE_HFS, ts);
  // basic four are good
  SCOPE_ASSERT_EQUAL("2020-01-07 02:40:22.1234567", ts.at("accessed"), "accessed");
  SCOPE_ASSERT_EQUAL("1970-01-01 08:42:17.1234564", ts.at("created"), "created");
  SCOPE_ASSERT_EQUAL("1977-06-02 18:24:30.315227845", ts.at("metadata"), "metadata");
  SCOPE_ASSERT_EQUAL("1979-12-16 02:27:45.999999999", ts.at("modified"), "modified");
  // and hfs+ backup
  SCOPE_ASSERT_EQUAL("2020-01-09 20:39:44.000001", ts.at("backup"), "backup");
  // but not these
  SCOPE_ASSERT(ts.at("deleted").is_null());
  SCOPE_ASSERT(ts.at("fn_accessed").is_null());
  SCOPE_ASSERT(ts.at("fn_created").is_null());
  SCOPE_ASSERT(ts.at("fn_metadata").is_null());
  SCOPE_ASSERT(ts.at("fn_modified").is_null());
}

SCOPE_TEST(testTskConvertLinuxTimestamps) {
  TSK_FS_META meta;
  meta.atime = 1578364822; // 2020-01-07 02:40:22
  meta.atime_nano = 123456700;
  meta.crtime = 31337; // 1970-01-01 08:42:17
  meta.crtime_nano = 123456400;
  meta.ctime = 234123870; // 1977-06-02 18:24:30
  meta.ctime_nano = 315227845;
  meta.mtime = 314159265; // 1979-12-16 02:27:45
  meta.mtime_nano = 999999999;

  meta.time2.hfs.bkup_time = 1578602384; // 2020-01-09 20:39:44
  meta.time2.hfs.bkup_time_nano = 1000;

  jsoncons::json ts;

  TskConverter munge;
  munge.convertTimestamps(meta, TSK_FS_TYPE_EXT4, ts);
  // basic four are good
  SCOPE_ASSERT_EQUAL("2020-01-07 02:40:22.1234567", ts.at("accessed"), "accessed");
  SCOPE_ASSERT_EQUAL("1970-01-01 08:42:17.1234564", ts.at("created"), "created");
  SCOPE_ASSERT_EQUAL("1977-06-02 18:24:30.315227845", ts.at("metadata"), "metadata");
  SCOPE_ASSERT_EQUAL("1979-12-16 02:27:45.999999999", ts.at("modified"), "modified");
  // and hfs+ backup
  SCOPE_ASSERT_EQUAL("2020-01-09 20:39:44.000001", ts.at("deleted"), "deleted");
  // but not these
  SCOPE_ASSERT(ts.at("backup").is_null());
  SCOPE_ASSERT(ts.at("fn_accessed").is_null());
  SCOPE_ASSERT(ts.at("fn_created").is_null());
  SCOPE_ASSERT(ts.at("fn_metadata").is_null());
  SCOPE_ASSERT(ts.at("fn_modified").is_null());
}

SCOPE_TEST(testTskConvertExtractString) {
  TskConverter munge;
  const char*  buf1 = "here is a \0string with a null in it";
  const char*  buf2 = "here is a cstring without any nulls";
  unsigned int bufLen = 35;

  SCOPE_ASSERT_EQUAL("here is a ", munge.extractString(buf1, bufLen));
  SCOPE_ASSERT_EQUAL("here is a cstring without any nulls", munge.extractString(buf2, bufLen));
}
