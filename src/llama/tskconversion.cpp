#include "tskconversion.h"

#include <algorithm>
#include <array>
#include <iterator>
#include <utility>

#include "hex.h"
#include "schema.h"

using namespace TskUtils;

std::string TskUtils::volumeSystemType(unsigned int type) {
  switch (type) {
  case TSK_VS_TYPE_DOS:
    return VS_TYPE_DOS;
  case TSK_VS_TYPE_BSD:
    return VS_TYPE_BSD;
  case TSK_VS_TYPE_SUN:
    return VS_TYPE_SUN;
  case TSK_VS_TYPE_MAC:
    return VS_TYPE_MAC;
  case TSK_VS_TYPE_GPT:
    return VS_TYPE_GPT;
  default:
    return VS_TYPE_UNKNOWN;
  }
}

std::string TskUtils::volumeFlags(unsigned int flags) {
  // I think these flags are mutually exclusive...
  switch (flags) {
  case TSK_VS_PART_FLAG_ALLOC:
    return VS_PART_FLAG_ALLOC;
  case TSK_VS_PART_FLAG_UNALLOC:
    return VS_PART_FLAG_UNALLOC;
  case TSK_VS_PART_FLAG_META:
    return VS_PART_FLAG_META;
  default:
    return "";
  }
}

std::string TskUtils::filesystemFlags(unsigned int flags) {
  const static std::array<std::pair<unsigned int, std::string>, 2> fmap{{
    {TSK_FS_INFO_FLAG_HAVE_SEQ,     FS_INFO_FLAG_HAVE_SEQ},
    {TSK_FS_INFO_FLAG_HAVE_NANOSEC, FS_INFO_FLAG_HAVE_NANOSEC}
  }};
  return flagsString(flags, fmap);
}

std::string TskUtils::nameType(unsigned int type) {
  switch (type) {
  case TSK_FS_NAME_TYPE_UNDEF:
    return TYPE_UNDEF;
  case TSK_FS_NAME_TYPE_FIFO:
    return TYPE_FIFO;
  case TSK_FS_NAME_TYPE_CHR:
    return TYPE_CHR;
  case TSK_FS_NAME_TYPE_DIR:
    return TYPE_DIR;
  case TSK_FS_NAME_TYPE_BLK:
    return TYPE_BLK;
  case TSK_FS_NAME_TYPE_REG:
    return TYPE_REG;
  case TSK_FS_NAME_TYPE_LNK:
    return TYPE_LNK;
  case TSK_FS_NAME_TYPE_SOCK:
    return TYPE_SOCK;
  case TSK_FS_NAME_TYPE_SHAD:
    return TYPE_SHAD;
  case TSK_FS_NAME_TYPE_WHT:
    return TYPE_WHT;
  case TSK_FS_NAME_TYPE_VIRT:
    return TYPE_VIRT;
  case TSK_FS_NAME_TYPE_VIRT_DIR:
    return TYPE_VIRT_DIR;
  default:
    return TYPE_UNDEF;
  }
}

std::string TskUtils::nameFlags(unsigned int flags) {
  const static std::array<std::pair<unsigned int, std::string>, 2> fmap{{
    {TSK_FS_NAME_FLAG_ALLOC,   NAME_FLAG_ALLOC},
    {TSK_FS_NAME_FLAG_UNALLOC, NAME_FLAG_UNALLOC}
  }};
  return flagsString(flags, fmap);
}

std::string TskUtils::metaType(unsigned int type) {
  switch (type) {
  case TSK_FS_META_TYPE_UNDEF:
    return TYPE_UNDEF;
  case TSK_FS_META_TYPE_REG:
    return TYPE_REG;
  case TSK_FS_META_TYPE_DIR:
    return TYPE_DIR;
  case TSK_FS_META_TYPE_FIFO:
    return TYPE_FIFO;
  case TSK_FS_META_TYPE_CHR:
    return TYPE_CHR;
  case TSK_FS_META_TYPE_BLK:
    return TYPE_BLK;
  case TSK_FS_META_TYPE_LNK:
    return TYPE_LNK;
  case TSK_FS_META_TYPE_SHAD:
    return TYPE_SHAD;
  case TSK_FS_META_TYPE_SOCK:
    return TYPE_SOCK;
  case TSK_FS_META_TYPE_WHT:
    return TYPE_WHT;
  case TSK_FS_META_TYPE_VIRT:
    return TYPE_VIRT;
  case TSK_FS_META_TYPE_VIRT_DIR:
    return TYPE_VIRT_DIR;
  default:
    return TYPE_UNDEF;
  }
}

std::string TskUtils::metaFlags(unsigned int flags) {
  const static std::array<std::pair<unsigned int, std::string>, 6> fmap{{
    {TSK_FS_META_FLAG_ALLOC,   META_FLAG_ALLOC},
    {TSK_FS_META_FLAG_UNALLOC, META_FLAG_UNALLOC},
    {TSK_FS_META_FLAG_USED,    META_FLAG_USED},
    {TSK_FS_META_FLAG_UNUSED,  META_FLAG_UNUSED},
    {TSK_FS_META_FLAG_COMP,    META_FLAG_COMP},
    {TSK_FS_META_FLAG_ORPHAN,  META_FLAG_ORPHAN}
  }};
  return flagsString(flags, fmap);
}

std::string TskUtils::attrType(unsigned int type) {
  switch (type) {
  case TSK_FS_ATTR_TYPE_NOT_FOUND: return ATTR_TYPE_NOT_FOUND;
  case TSK_FS_ATTR_TYPE_DEFAULT: return ATTR_TYPE_DEFAULT; // default _is_ data, so match up with NTFS Data
  case TSK_FS_ATTR_TYPE_NTFS_SI: return ATTR_TYPE_NTFS_SI;
  case TSK_FS_ATTR_TYPE_NTFS_ATTRLIST: return ATTR_TYPE_NTFS_ATTRLIST;
  case TSK_FS_ATTR_TYPE_NTFS_FNAME: return ATTR_TYPE_NTFS_FNAME;
  case TSK_FS_ATTR_TYPE_NTFS_OBJID: return ATTR_TYPE_NTFS_OBJID;
  case TSK_FS_ATTR_TYPE_NTFS_SEC: return ATTR_TYPE_NTFS_SEC;
  case TSK_FS_ATTR_TYPE_NTFS_VNAME: return ATTR_TYPE_NTFS_VNAME;
  case TSK_FS_ATTR_TYPE_NTFS_VINFO: return ATTR_TYPE_NTFS_VINFO;
  case TSK_FS_ATTR_TYPE_NTFS_DATA: return ATTR_TYPE_NTFS_DATA;
  case TSK_FS_ATTR_TYPE_NTFS_IDXROOT: return ATTR_TYPE_NTFS_IDXROOT;
  case TSK_FS_ATTR_TYPE_NTFS_IDXALLOC: return ATTR_TYPE_NTFS_IDXALLOC;
  case TSK_FS_ATTR_TYPE_NTFS_BITMAP: return ATTR_TYPE_NTFS_BITMAP;
  case TSK_FS_ATTR_TYPE_NTFS_SYMLNK: return ATTR_TYPE_NTFS_SYMLNK;
  // Reparse points are a Win2K feature and use the same type code as symlink.
  // So this is technically ambiguous. To bite the bullet, we go with symlinks.
//  case TSK_FS_ATTR_TYPE_NTFS_REPARSE: return ATTR_TYPE_NTFS_REPARSE;
  case TSK_FS_ATTR_TYPE_NTFS_EAINFO: return ATTR_TYPE_NTFS_EAINFO;
  case TSK_FS_ATTR_TYPE_NTFS_EA: return ATTR_TYPE_NTFS_EA;
  case TSK_FS_ATTR_TYPE_NTFS_PROP: return ATTR_TYPE_NTFS_PROP;
  case TSK_FS_ATTR_TYPE_NTFS_LOG: return ATTR_TYPE_NTFS_LOG;

  case TSK_FS_ATTR_TYPE_UNIX_INDIR: return ATTR_TYPE_UNIX_INDIR;
  case TSK_FS_ATTR_TYPE_UNIX_EXTENT: return ATTR_TYPE_UNIX_EXTENT;

  // Types for HFS+ File Attributes
//  case TSK_FS_ATTR_TYPE_HFS_DEFAULT: return ATTR_TYPE_HFS_DEFAULT;
  case TSK_FS_ATTR_TYPE_HFS_DATA: return ATTR_TYPE_HFS_DATA;
  case TSK_FS_ATTR_TYPE_HFS_RSRC: return ATTR_TYPE_HFS_RSRC;
  case TSK_FS_ATTR_TYPE_HFS_EXT_ATTR: return ATTR_TYPE_HFS_EXT_ATTR;
  case TSK_FS_ATTR_TYPE_HFS_COMP_REC: return ATTR_TYPE_HFS_COMP_REC;
  default:
    return ATTR_TYPE_UNKNOWN;
  }
}

std::string TskUtils::attrFlags(unsigned int flags) {
  static std::array<std::pair<unsigned int, std::string>, 7> fmap{{
    {TSK_FS_ATTR_INUSE,    ATTR_FLAG_INUSE},
    {TSK_FS_ATTR_NONRES,   ATTR_FLAG_NONRES},
    {TSK_FS_ATTR_RES,      ATTR_FLAG_RES},
    {TSK_FS_ATTR_ENC,      ATTR_FLAG_ENC},
    {TSK_FS_ATTR_COMP,     ATTR_FLAG_COMP},
    {TSK_FS_ATTR_SPARSE,   ATTR_FLAG_SPARSE},
    {TSK_FS_ATTR_RECOVERY, ATTR_FLAG_RECOVERY}
  }};
  return flagsString(flags, fmap);
}

std::string TskUtils::nrdRunFlags(unsigned int flags) {
  switch (flags) {
  case TSK_FS_ATTR_RUN_FLAG_NONE:
    return ATTR_RUN_FLAG_NONE;
  case TSK_FS_ATTR_RUN_FLAG_FILLER:
    return ATTR_RUN_FLAG_FILLER;
  case TSK_FS_ATTR_RUN_FLAG_SPARSE:
    return ATTR_RUN_FLAG_SPARSE;
  }
  return "";
}

std::string TskUtils::filesystemID(const uint8_t* id, size_t len, bool le) {
  if (le) {
    // FIXME: wtf, this came from fsrip, but is it really correct that the
    // endianness applies to the fs id?!

    // little-endian filesystem, reverse the id
    const std::vector<uint8_t> v(
      std::make_reverse_iterator(id + len),
      std::make_reverse_iterator(id)
    );
    return hexEncode(v.data(), v.data() + len);
  }
  else {
    return hexEncode(id, len);
  }
}

jsoncons::json TskUtils::convertName(const TSK_FS_NAME& name) {
  return jsoncons::json(
    jsoncons::json_object_arg,
    {
      { "name",       extractString(name.name, name.name_size) },
      { "shrt_name",  extractString(name.shrt_name, name.shrt_name_size) },
      { "meta_addr",  name.meta_addr },
      { "meta_seq",   name.meta_seq },
      { "par_addr",   name.par_addr },
      { "par_seq",    name.par_seq },
//      { "date_added", name.date_added },
      { "type",       nameType(name.type) },
      { "flags",      nameFlags(name.flags) }
    }
  );
}

jsoncons::json TskUtils::convertMeta(const TSK_FS_META& meta, TimestampGetter& ts) {
  return jsoncons::json(
    jsoncons::json_object_arg,
    {
      { "addr",  meta.addr },
      { "flags", metaFlags(meta.flags) },
      { "type",  metaType(meta.type) },
      { "uid",   std::to_string(meta.uid) },
      { "gid",   std::to_string(meta.gid) },
      { "link",  meta.link ? meta.link : "" },
      { "nlink", meta.nlink },
      { "seq",   meta.seq },
      { "attrs", jsoncons::json(jsoncons::json_array_arg) },
      { "accessed",    ts.accessed(meta) },
      { "created",     ts.created(meta) },
      { "metadata",    ts.metadata(meta) },
      { "modified",    ts.modified(meta) },
      { "deleted",     ts.deleted(meta) },
      { "backup",      ts.backup(meta) },
      { "fn_accessed", ts.fn_accessed(meta) },
      { "fn_created",  ts.fn_created(meta) },
      { "fn_metadata", ts.fn_metadata(meta) },
      { "fn_modified", ts.fn_modified(meta) }
    }
  );
}

std::unique_ptr<TimestampGetter> TskUtils::makeTimestampGetter(TSK_FS_TYPE_ENUM fstype) {
  switch (fstype) {
  case TSK_FS_TYPE_NTFS:
    return std::make_unique<NTFSTimestampGetter>();
  case TSK_FS_TYPE_FFS1: // need to double-check this list
  case TSK_FS_TYPE_FFS1B:
  case TSK_FS_TYPE_FFS2:
  case TSK_FS_TYPE_EXT2:
  case TSK_FS_TYPE_EXT3:
  case TSK_FS_TYPE_EXT4:
    return std::make_unique<EXTTimestampGetter>();
  case TSK_FS_TYPE_HFS:
    return std::make_unique<HFSTimestampGetter>();
  default:
    return std::make_unique<CommonTimestampGetter>();
  }
}

std::string TskUtils::extractString(const char* str, unsigned int size) {
  return std::string(str, std::find(str, str + size, '\0'));
}

jsoncons::json TskUtils::convertAttr(const TSK_FS_ATTR& attr) {
  jsoncons::json jsAttr(
    jsoncons::json_object_arg,
    {
      { "id", attr.id },
      { "flags", attrFlags(attr.flags) },
      { "name", extractString(attr.name, attr.name_size) },
      { "size", attr.size },
      { "type", attrType(attr.type) }
    }
  );

  if (attr.flags & TSK_FS_ATTR_RES) {
    // resident
    jsAttr["rd_buf"] = hexEncode(attr.rd.buf, std::min(attr.size, static_cast<int64_t>(attr.rd.buf_size)));
    jsAttr["rd_offset"] = attr.rd.offset;
  }
  else {
    // non-resident
    jsAttr["nrd_allocsize"] = attr.nrd.allocsize;
    jsAttr["nrd_compsize"] = attr.nrd.compsize;
    jsAttr["nrd_initsize"] = attr.nrd.initsize;
    jsAttr["nrd_skiplen"] = attr.nrd.skiplen;

    jsoncons::json nrd_runs = jsoncons::json(jsoncons::json_array_arg);
    for (auto i = attr.nrd.run; i; i = i->next) {
      if (i->flags == TSK_FS_ATTR_RUN_FLAG_FILLER) {
        // TODO: check on the exact semantics of this flag
        continue;
      }

      nrd_runs.push_back(TskUtils::convertNRDR(*i));

      if (i == attr.nrd.run_end) {
        // this is hopefully unnecessary, but what if
        // attr.nrd.run_end.next isn't null?
        // paranoia is a feature
        break;
      }
    }

    jsAttr["nrd_runs"] = std::move(nrd_runs);
  }

  return jsAttr;
}

jsoncons::json TskUtils::convertNRDR(const TSK_FS_ATTR_RUN& dataRun) {
  return jsoncons::json(
    jsoncons::json_object_arg,
    {
      { "addr",  dataRun.addr },
      { "flags", nrdRunFlags(dataRun.flags) },
      { "len",   dataRun.len },
      { "offset", dataRun.offset }
    }
  );
}

jsoncons::json TskUtils::convertImg(const TSK_IMG_INFO& img) {
  return jsoncons::json(
    jsoncons::json_object_arg,
    {
      { "type", tsk_img_type_toname(img.itype) },
      { "description", tsk_img_type_todesc(img.itype) },
      { "size", img.size },
      { "sectorSize", img.sector_size }
    }
  );
}

jsoncons::json TskUtils::convertVS(const TSK_VS_INFO& vs) {
  return jsoncons::json(
    jsoncons::json_object_arg,
    {
      { "type", volumeSystemType(vs.vstype) },
      { "description", tsk_vs_type_todesc(vs.vstype) },
      { "blockSize", vs.block_size },
      { "numVolumes", vs.part_count },
      { "offset", vs.offset },
      { "volumes", jsoncons::json(jsoncons::json_array_arg) }
    }
  );
}

jsoncons::json TskUtils::convertVol(const TSK_VS_PART_INFO& vol) {
  return jsoncons::json(
    jsoncons::json_object_arg,
    {
      { "addr", vol.addr },
      { "description", vol.desc },
      { "flags", volumeFlags(vol.flags) },
      { "numBlocks", vol.len },
      { "slotNum", vol.slot_num },
      { "startBlock", vol.start },
      { "tableNum", vol.table_num }
    }
  );
}

jsoncons::json TskUtils::convertFS(const TSK_FS_INFO& fs) {
  const bool littleEndian = fs.endian == TSK_LIT_ENDIAN;

  return jsoncons::json(
    jsoncons::json_object_arg,
    {
      { "numBlocks", fs.block_count },
      { "blockSize", fs.block_size },
      { "deviceBlockSize", fs.dev_bsize },
      { "blockName", fs.duname },
      { "littleEndian", littleEndian },
      { "firstBlock", fs.first_block },
      { "firstInum", fs.first_inum },
      { "flags", filesystemFlags(fs.flags) },
      { "fsID", filesystemID(fs.fs_id, fs.fs_id_used, littleEndian) },
      { "type", tsk_fs_type_toname(fs.ftype) },
      { "journalInum", fs.journ_inum },
      { "numInums", fs.inum_count },
      { "lastBlock", fs.last_block },
      { "lastBlockAct", fs.last_block_act },
      { "lastInum", fs.last_inum },
      { "byteOffset", fs.offset },
      { "rootInum", fs.root_inum }
    }
  );
}
