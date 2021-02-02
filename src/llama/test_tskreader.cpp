#include <scope/test.h>

#include <cstring>

#include "tskreader.h"

#include "mockinputhandler.h"
#include "mockoutputhandler.h"

void noop_deleter(TSK_IMG_INFO*) {}

class StubTskWrapper {
public:
  StubTskWrapper() {
    std::memset(&img, 0, sizeof(img));
    img.itype = TSK_IMG_TYPE_EWF_EWF;
    img.size = 1;
    img.num_img = 2;
    img.sector_size = 3;
    img.page_size = 4;
    img.spare_size = 5;
  }

  std::unique_ptr<TSK_IMG_INFO, void(*)(TSK_IMG_INFO*)> openImg(const char* path) {
    return {&img, noop_deleter};
  }

  std::unique_ptr<TSK_FS_INFO, void(*)(TSK_FS_INFO*)> openFS(TSK_IMG_INFO* img, TSK_OFF_T off, TSK_FS_TYPE_ENUM type) const {
    return {nullptr, nullptr};
  }

  std::unique_ptr<TSK_FS_FILE, void(*)(TSK_FS_FILE*)> openFile(TSK_FS_INFO* fs, TSK_INUM_T inum) const {
    return {nullptr, nullptr};
  }

  void populateAttrs(TSK_FS_FILE* file) const {
  }

private:
  TSK_IMG_INFO img;
};

class StubTskWalker {
public:
  bool walk(
    TSK_IMG_INFO* info,
    std::function<TSK_FILTER_ENUM(const TSK_VS_INFO*)> vs_cb,
    std::function<TSK_FILTER_ENUM(const TSK_VS_PART_INFO*)> vol_cb,
    std::function<TSK_FILTER_ENUM(TSK_FS_INFO*)> fs_cb,
    std::function<TSK_RETVAL_ENUM(TSK_FS_FILE*, const char*)> file_cb
  )
  {
    TSK_VS_INFO vs;
    std::memset(&vs, 0, sizeof(vs));

    vs.vstype = TSK_VS_TYPE_BSD;
    vs.is_backup = 1;
    vs.offset = 2;
    vs.block_size = 3;
    vs.endian = TSK_BIG_ENDIAN;
    vs.part_count = 4;

    vs_cb(&vs);

    TSK_VS_PART_INFO vol;
    std::memset(&vol, 0, sizeof(vol));

    vol.start = 1;
    vol.len = 11; // this volume goes to 11
    vol.desc = const_cast<char*>("TURN IT UP");
    vol.table_num = 2;
    vol.slot_num = 3;
    vol.addr = 4;
    vol.flags = TSK_VS_PART_FLAG_META;

    vol_cb(&vol);

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

    fs_cb(&fs);

    return true;
  }
};

SCOPE_TEST(testMakeTskReader) {
  TskReader<StubTskWrapper, StubTskWalker> r("bogus.E01");

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
      { "description", "Expert Witness Format (EnCase)" },
      { "sectorSize", 3 },
      { "size", 1 },
      { "type", "ewf" },
      {
        "volumeSystem",
        jsoncons::json(
          jsoncons::json_object_arg,
          {
            { "blockSize", 3 },
            { "description", "BSD Disk Label" },
            { "numVolumes", 4 },
            { "offset", 2 },
            { "type", "BSD" },
            {
              "volumes",
              jsoncons::json(
                jsoncons::json_array_arg,
                {
                  jsoncons::json(
                    jsoncons::json_object_arg,
                    {
                      { "addr", 4 },
                      { "description", "TURN IT UP" },
                      { "flags", "Volume System" },
                      { "numBlocks", 11 },
                      { "slotNum", 3 },
                      { "startBlock", 1 },
                      { "tableNum", 2 },
                      {
                        "fileSystem",
                        jsoncons::json(
                          jsoncons::json_object_arg,
                          {
                            { "blockName", "whatever" },
                            { "blockSize", 9 },
                            { "byteOffset", 1 },
                            { "deviceBlockSize", 10 },
                            { "firstBlock", 7 },
                            { "firstInum", 4 },
                            { "flags", "Sequenced, Nanosecond precision" },
                            { "fsID", "0123456789abcdef" },
                            { "journalInum", 13 },
                            { "lastBlock", 8 },
                            { "lastBlockAct", 0 },
                            { "lastInum", 5 },
                            { "littleEndian", false },
                            { "numBlocks", 6 },
                            { "numInums", 2 },
                            { "rootInum", 3 },
                            { "type", "fat16" }
                          }
                        )
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
