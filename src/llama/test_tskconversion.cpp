#include <scope/test.h>

#include "tskconversion.h"

SCOPE_TEST(textExtractString) {
  using namespace TskUtils;
  SCOPE_ASSERT_EQUAL("", extractString("", 0));
  SCOPE_ASSERT_EQUAL("abcde", extractString("abcdefg", 5));
  SCOPE_ASSERT_EQUAL("abc", extractString("abc\0defg", 5));
}

SCOPE_TEST(testFlagsString) {
  using namespace TskUtils;

  const static std::array<std::pair<unsigned int, std::string>, 3> fmap{{
    {0b001, "one"},
    {0b010, "two"},
    {0b100, "three"}
  }};

  SCOPE_ASSERT_EQUAL("", flagsString(0, fmap));
  SCOPE_ASSERT_EQUAL("one", flagsString(1, fmap));
  SCOPE_ASSERT_EQUAL("two", flagsString(2, fmap));
  SCOPE_ASSERT_EQUAL("one, two", flagsString(3, fmap));
  SCOPE_ASSERT_EQUAL("three", flagsString(4, fmap));
  SCOPE_ASSERT_EQUAL("one, three", flagsString(5, fmap));
  SCOPE_ASSERT_EQUAL("two, three", flagsString(6, fmap));
  SCOPE_ASSERT_EQUAL("one, two, three", flagsString(7, fmap));
  SCOPE_ASSERT_EQUAL("", flagsString(8, fmap));
}

SCOPE_TEST(testTskVolumeSystemType) {
  using namespace TskUtils;
  SCOPE_ASSERT_EQUAL("Unknown", volumeSystemType(0));
  SCOPE_ASSERT_EQUAL("MBR", volumeSystemType(1));
  SCOPE_ASSERT_EQUAL("BSD", volumeSystemType(2));
  SCOPE_ASSERT_EQUAL("Sun", volumeSystemType(4));
  SCOPE_ASSERT_EQUAL("Macintosh", volumeSystemType(8));
  SCOPE_ASSERT_EQUAL("GPT", volumeSystemType(16));
  SCOPE_ASSERT_EQUAL("Unknown", volumeSystemType(0xffff));
}

SCOPE_TEST(testTskVolumeFlags) {
  using namespace TskUtils;
  SCOPE_ASSERT_EQUAL("", volumeFlags(0));
  SCOPE_ASSERT_EQUAL("Allocated", volumeFlags(1));
  SCOPE_ASSERT_EQUAL("Unallocated", volumeFlags(2));
  SCOPE_ASSERT_EQUAL("", volumeFlags(3));
  SCOPE_ASSERT_EQUAL("Volume System", volumeFlags(4));
  SCOPE_ASSERT_EQUAL("", volumeFlags(5));
  // I don't think there's much point in testing for that "ALL" enum
}

SCOPE_TEST(testTskFilesystemFlags) {
  using namespace TskUtils;
  SCOPE_ASSERT_EQUAL("", filesystemFlags(0));
  SCOPE_ASSERT_EQUAL("Sequenced", filesystemFlags(1));
  SCOPE_ASSERT_EQUAL("Nanosecond precision", filesystemFlags(2));
  SCOPE_ASSERT_EQUAL("Sequenced, Nanosecond precision", filesystemFlags(3));
}

SCOPE_TEST(testTskNameType) {
  using namespace TskUtils;
  SCOPE_ASSERT_EQUAL("Undefined", nameType(0));
  SCOPE_ASSERT_EQUAL("Named Pipe", nameType(1));
  SCOPE_ASSERT_EQUAL("Character Device", nameType(2));
  SCOPE_ASSERT_EQUAL("Folder", nameType(3));
  SCOPE_ASSERT_EQUAL("Block Device", nameType(4));
  SCOPE_ASSERT_EQUAL("File", nameType(5));
  SCOPE_ASSERT_EQUAL("Symbolic Link", nameType(6));
  SCOPE_ASSERT_EQUAL("Domain Socket", nameType(7));
  SCOPE_ASSERT_EQUAL("Shadow Inode", nameType(8));
  SCOPE_ASSERT_EQUAL("Whiteout Inode", nameType(9));
  SCOPE_ASSERT_EQUAL("Virtual", nameType(10));
  SCOPE_ASSERT_EQUAL("Virtual Folder", nameType(11));
  SCOPE_ASSERT_EQUAL("Undefined", nameType(12));
}

SCOPE_TEST(testTskNameFlags) {
  using namespace TskUtils;
  SCOPE_ASSERT_EQUAL("Allocated", nameFlags(1));
  SCOPE_ASSERT_EQUAL("Deleted", nameFlags(2));
}

SCOPE_TEST(testTskMetaType) {
  // Seriously, same shit as name type, different order
  using namespace TskUtils;
  SCOPE_ASSERT_EQUAL("Undefined", metaType(0));
  SCOPE_ASSERT_EQUAL("File", metaType(1));
  SCOPE_ASSERT_EQUAL("Folder", metaType(2));
  SCOPE_ASSERT_EQUAL("Named Pipe", metaType(3));
  SCOPE_ASSERT_EQUAL("Character Device", metaType(4));
  SCOPE_ASSERT_EQUAL("Block Device", metaType(5));
  SCOPE_ASSERT_EQUAL("Symbolic Link", metaType(6));
  SCOPE_ASSERT_EQUAL("Shadow Inode", metaType(7));
  SCOPE_ASSERT_EQUAL("Domain Socket", metaType(8));
  SCOPE_ASSERT_EQUAL("Whiteout Inode", metaType(9));
  SCOPE_ASSERT_EQUAL("Virtual", metaType(10));
  SCOPE_ASSERT_EQUAL("Virtual Folder", metaType(11));
  SCOPE_ASSERT_EQUAL("Undefined", metaType(12));
}

SCOPE_TEST(testTskMetaFlags) {
  using namespace TskUtils;
  SCOPE_ASSERT_EQUAL("Allocated", metaFlags(1));
  SCOPE_ASSERT_EQUAL("Deleted", metaFlags(2));
  SCOPE_ASSERT_EQUAL("Used", metaFlags(4));
  SCOPE_ASSERT_EQUAL("Unused", metaFlags(8));
  SCOPE_ASSERT_EQUAL("Compressed", metaFlags(16));
  SCOPE_ASSERT_EQUAL("Orphan", metaFlags(32));
  SCOPE_ASSERT_EQUAL("Deleted, Used", metaFlags(6));
}

SCOPE_TEST(testTskAttrType) {
  using namespace TskUtils;
  SCOPE_ASSERT_EQUAL("Unknown", attrType(TSK_FS_ATTR_TYPE_NOT_FOUND));
  SCOPE_ASSERT_EQUAL("Data", attrType(TSK_FS_ATTR_TYPE_DEFAULT)); // default _is_ data, so match up with NTFS Data
  SCOPE_ASSERT_EQUAL("Standard Information", attrType(TSK_FS_ATTR_TYPE_NTFS_SI));
  SCOPE_ASSERT_EQUAL("NTFS Attributes", attrType(TSK_FS_ATTR_TYPE_NTFS_ATTRLIST));
  SCOPE_ASSERT_EQUAL("Filename", attrType(TSK_FS_ATTR_TYPE_NTFS_FNAME));
  SCOPE_ASSERT_EQUAL("ObjID", attrType(TSK_FS_ATTR_TYPE_NTFS_OBJID));
  SCOPE_ASSERT_EQUAL("Sec", attrType(TSK_FS_ATTR_TYPE_NTFS_SEC));
  SCOPE_ASSERT_EQUAL("VName", attrType(TSK_FS_ATTR_TYPE_NTFS_VNAME));
  SCOPE_ASSERT_EQUAL("VInfo", attrType(TSK_FS_ATTR_TYPE_NTFS_VINFO));
  SCOPE_ASSERT_EQUAL("Data", attrType(TSK_FS_ATTR_TYPE_NTFS_DATA));
  SCOPE_ASSERT_EQUAL("IdxRoot", attrType(TSK_FS_ATTR_TYPE_NTFS_IDXROOT));
  SCOPE_ASSERT_EQUAL("IdxAlloc", attrType(TSK_FS_ATTR_TYPE_NTFS_IDXALLOC));
  SCOPE_ASSERT_EQUAL("Bitmap", attrType(TSK_FS_ATTR_TYPE_NTFS_BITMAP));
  SCOPE_ASSERT_EQUAL("Symlink", attrType(TSK_FS_ATTR_TYPE_NTFS_SYMLNK));

  // It would be great if this would return Reparse, but it can't because
  // reparse has the same typecode as symlink. So instead we assert the
  // broken behavior. This was a change from Win2K and WinXP.
  SCOPE_ASSERT_EQUAL("Symlink", attrType(TSK_FS_ATTR_TYPE_NTFS_REPARSE));

  SCOPE_ASSERT_EQUAL("EAInfo", attrType(TSK_FS_ATTR_TYPE_NTFS_EAINFO));
  SCOPE_ASSERT_EQUAL("EA", attrType(TSK_FS_ATTR_TYPE_NTFS_EA));
  SCOPE_ASSERT_EQUAL("Prop", attrType(TSK_FS_ATTR_TYPE_NTFS_PROP));
  SCOPE_ASSERT_EQUAL("Log", attrType(TSK_FS_ATTR_TYPE_NTFS_LOG));

  SCOPE_ASSERT_EQUAL("Indirect", attrType(TSK_FS_ATTR_TYPE_UNIX_INDIR));
  SCOPE_ASSERT_EQUAL("Extents", attrType(TSK_FS_ATTR_TYPE_UNIX_EXTENT));

  // Types for HFS+ File Attributes
  SCOPE_ASSERT_EQUAL("Data", attrType(TSK_FS_ATTR_TYPE_HFS_DEFAULT));
  SCOPE_ASSERT_EQUAL("Data", attrType(TSK_FS_ATTR_TYPE_HFS_DATA));
  SCOPE_ASSERT_EQUAL("Resource", attrType(TSK_FS_ATTR_TYPE_HFS_RSRC));
  SCOPE_ASSERT_EQUAL("EA", attrType(TSK_FS_ATTR_TYPE_HFS_EXT_ATTR));
  SCOPE_ASSERT_EQUAL("Compressed", attrType(TSK_FS_ATTR_TYPE_HFS_COMP_REC));
}

SCOPE_TEST(testTskAttrFlags) {
  using namespace TskUtils;
  SCOPE_ASSERT_EQUAL("", attrFlags(0));
  SCOPE_ASSERT_EQUAL("In Use", attrFlags(1));
  SCOPE_ASSERT_EQUAL("Non-resident", attrFlags(2));
  SCOPE_ASSERT_EQUAL("Resident", attrFlags(4));
  SCOPE_ASSERT_EQUAL("Encrypted", attrFlags(16));
  SCOPE_ASSERT_EQUAL("Compressed", attrFlags(32));
  SCOPE_ASSERT_EQUAL("Sparse", attrFlags(64));
  SCOPE_ASSERT_EQUAL("Recovered", attrFlags(128));
  SCOPE_ASSERT_EQUAL("In Use, Non-resident", attrFlags(3));
}

SCOPE_TEST(testTskNrdRunFlags) {
  using namespace TskUtils;
  SCOPE_ASSERT_EQUAL("", nrdRunFlags(TSK_FS_ATTR_RUN_FLAG_NONE));
  SCOPE_ASSERT_EQUAL("Filler", nrdRunFlags(TSK_FS_ATTR_RUN_FLAG_FILLER));
  SCOPE_ASSERT_EQUAL("Sparse", nrdRunFlags(TSK_FS_ATTR_RUN_FLAG_SPARSE));
}

SCOPE_TEST(testTskFileSystemID) {
  using namespace TskUtils;
  const uint8_t id[] = { 0xDE, 0xAD, 0xBE, 0xEF };
  SCOPE_ASSERT_EQUAL("deadbeef", filesystemID(id, sizeof(id), false));
  SCOPE_ASSERT_EQUAL("efbeadde", filesystemID(id, sizeof(id), true));
}

SCOPE_TEST(testTskConvertFS) {
  TSK_FS_INFO fs;
  std::memset(&fs, 0, sizeof(fs));

  fs.offset = 1;
  fs.inum_count = 2;
  fs.root_inum = 3;
  fs.first_inum = 4;
  fs.last_inum = 5;
  fs.block_count = 6;
  fs.first_block = 7;
  fs.last_block = 8;
  fs.block_size = 9;
  fs.dev_bsize = 10;
  fs.block_pre_size = 11;
  fs.block_post_size = 12;
  fs.journ_inum = 13;
  fs.ftype = TSK_FS_TYPE_FAT16;
  fs.duname = "whatever";
  fs.flags = static_cast<TSK_FS_INFO_FLAG_ENUM>(TSK_FS_INFO_FLAG_HAVE_SEQ | TSK_FS_INFO_FLAG_HAVE_NANOSEC);
  SCOPE_ASSERT(8 <= TSK_FS_INFO_FS_ID_LEN);
  fs.fs_id[0] = 0x01;
  fs.fs_id[1] = 0x23;
  fs.fs_id[2] = 0x45;
  fs.fs_id[3] = 0x67;
  fs.fs_id[4] = 0x89;
  fs.fs_id[5] = 0xAB;
  fs.fs_id[6] = 0xCD;
  fs.fs_id[7] = 0xEF;
  fs.fs_id_used = 8;
  fs.endian = TSK_BIG_ENDIAN;

  const jsoncons::json js = TskUtils::convertFS(fs);
  const std::string expected = "{\"blockName\":\"whatever\",\"blockSize\":9,\"byteOffset\":1,\"deviceBlockSize\":10,\"firstBlock\":7,\"firstInum\":4,\"flags\":\"Sequenced, Nanosecond precision\",\"fsID\":\"0123456789abcdef\",\"journalInum\":13,\"lastBlock\":8,\"lastBlockAct\":0,\"lastInum\":5,\"littleEndian\":false,\"numBlocks\":6,\"numInums\":2,\"rootInum\":3,\"type\":\"fat16\"}";
  const std::string actual = js.as<std::string>();
  SCOPE_ASSERT_EQUAL(expected, actual);
}

SCOPE_TEST(testTskConvertVol) {
  TSK_VS_PART_INFO vol;
  std::memset(&vol, 0, sizeof(vol));

  vol.start = 1;
  vol.len = 11; // this volume goes to 11
  vol.desc = const_cast<char*>("TURN IT UP");
  vol.table_num = 2;
  vol.slot_num = 3;
  vol.addr = 4;
  vol.flags = TSK_VS_PART_FLAG_META;

  const jsoncons::json js = TskUtils::convertVol(vol);
  const std::string expected = "{\"addr\":4,\"description\":\"TURN IT UP\",\"flags\":\"Volume System\",\"numBlocks\":11,\"slotNum\":3,\"startBlock\":1,\"tableNum\":2}";
  const std::string actual = js.as<std::string>();
  SCOPE_ASSERT_EQUAL(expected, actual);
}

SCOPE_TEST(testTskConvertVS) {
  TSK_VS_INFO vs;
  std::memset(&vs, 0, sizeof(vs));

  vs.vstype = TSK_VS_TYPE_BSD;
  vs.is_backup = 1;
  vs.offset = 2;
  vs.block_size = 3;
  vs.endian = TSK_BIG_ENDIAN;
  vs.part_count = 4;

  const jsoncons::json js = TskUtils::convertVS(vs);
  const std::string expected = "{\"blockSize\":3,\"description\":\"BSD Disk Label\",\"numVolumes\":4,\"offset\":2,\"type\":\"BSD\",\"volumes\":[]}";
  const std::string actual = js.as<std::string>();
  SCOPE_ASSERT_EQUAL(expected, actual);
}

SCOPE_TEST(testTskConvertImg) {
  TSK_IMG_INFO img;
  std::memset(&img, 0, sizeof(img));

  img.itype = TSK_IMG_TYPE_EWF_EWF;
  img.size = 1;
  img.num_img = 2;
  img.sector_size = 3;
  img.page_size = 4;
  img.spare_size = 5;

  const jsoncons::json js = TskUtils::convertImg(img);
  const std::string expected = "{\"description\":\"Expert Witness Format (EnCase)\",\"sectorSize\":3,\"size\":1,\"type\":\"ewf\"}";
  const std::string actual = js.as<std::string>();
  SCOPE_ASSERT_EQUAL(expected, actual);
}

SCOPE_TEST(testTskConvertNRDs) {
  TSK_FS_ATTR_RUN nrd;
  std::memset(&nrd, 0, sizeof(nrd));

  nrd.addr   = 15;
  nrd.len    = 3045;
  nrd.offset = 17;
  nrd.flags  = TSK_FS_ATTR_RUN_FLAG_SPARSE;

  const jsoncons::json js = TskUtils::convertNRDR(nrd);
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
  std::memset(&attr, 0, sizeof(attr));
  setResAttr(attr);

  const jsoncons::json js = TskUtils::convertAttr(attr);
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
  TSK_FS_ATTR_RUN nrd1;
  std::memset(&nrd1, 0, sizeof(nrd1));

  TSK_FS_ATTR_RUN nrd2;
  std::memset(&nrd2, 0, sizeof(nrd2));

  TSK_FS_ATTR attr;
  std::memset(&attr, 0, sizeof(attr));
  setNonresAttr(attr, nrd1, nrd2);

  const jsoncons::json js = TskUtils::convertAttr(attr);
  testNonresAttr(js);
}

SCOPE_TEST(testTskMetaConvert) {
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

  meta.atime = 1578364822; // 2020-01-07 02:40:22
  meta.atime_nano = 123456700;
  meta.crtime = 31337;     // 1970-01-01 08:42:17
  meta.crtime_nano = 123456400;
  meta.ctime = 234123870;  // 1977-06-02 18:24:30
  meta.ctime_nano = 315227845;
  meta.mtime = 314159265;  // 1979-12-16 02:27:45
  meta.mtime_nano = 999999999;

  // meta.name2 = "SHRTNM~2";

  CommonTimestampGetter tsg;
  jsoncons::json js = TskUtils::convertMeta(meta, tsg);

  SCOPE_ASSERT_EQUAL(17, js["addr"]);
  SCOPE_ASSERT_EQUAL("Deleted", js["flags"]);
  SCOPE_ASSERT_EQUAL("File", js["type"]);

  SCOPE_ASSERT_EQUAL("21", js["uid"]); // stringized
  SCOPE_ASSERT_EQUAL("1026", js["gid"]); // also stringized

  SCOPE_ASSERT_EQUAL("I_am_the_target", js["link"]);
  SCOPE_ASSERT_EQUAL(2, js["nlink"]);
  SCOPE_ASSERT_EQUAL(8, js["seq"]);
  // SCOPE_ASSERT_EQUAL("SHRTNM~2", js["name2"]);

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
  js = TskUtils::convertMeta(meta, tsg);
  SCOPE_ASSERT_EQUAL("", js["link"]);
}

SCOPE_TEST(testTskNameConvert) {
  TSK_FS_NAME name;
  std::memset(&name, 0, sizeof(name));

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

  const jsoncons::json js = TskUtils::convertName(name);

  SCOPE_ASSERT_EQUAL("woowoowoo", js["name"]);
  SCOPE_ASSERT_EQUAL("WOOWOO~1", js["shrt_name"]);
  SCOPE_ASSERT_EQUAL(7, js["meta_addr"]);
  SCOPE_ASSERT_EQUAL(6, js["meta_seq"]);
  SCOPE_ASSERT_EQUAL(231, js["par_addr"]);
  SCOPE_ASSERT_EQUAL(72, js["par_seq"]);
  SCOPE_ASSERT_EQUAL("Domain Socket", js["type"]);
  SCOPE_ASSERT_EQUAL("Allocated", js["flags"]);
}
