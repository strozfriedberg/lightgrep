#include "tskconversion.h"

#include <algorithm>
#include <array>
#include <utility>

#include <boost/date_time/posix_time/posix_time.hpp>

#include "hex.h"
#include "schema.h"

using namespace TskUtils;

TskConverter::TskConverter()
{
  NanoBuf << std::fixed << std::setprecision(9);
}

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

jsoncons::json TskConverter::convertFile(TSK_FS_FILE& file) {
  // ridiculous bullshit to force attrs to be populated
  tsk_fs_file_attr_get_idx(&file, 0);

  jsoncons::json doc(jsoncons::json_object_arg);

  if (file.meta) {
    doc["meta"] = convertMeta(*file.meta, file.fs_info->ftype);
  }

  if (file.name) {
    doc["name"] = convertName(*file.name);
  }

  return doc;
}

jsoncons::json TskConverter::convertName(const TSK_FS_NAME& name) const {
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

jsoncons::json TskConverter::convertAttrs(const TSK_FS_META& meta) const {
  jsoncons::json jsAttrs(jsoncons::json_array_arg);

  if (meta.attr) {
    for (const TSK_FS_ATTR* a = meta.attr->head; a; a = a->next) {
      if (a->flags & TSK_FS_ATTR_INUSE) {
        jsAttrs.push_back(convertAttr(*a));
      }
    }
  }

  return jsAttrs;
}

jsoncons::json TskConverter::convertMeta(const TSK_FS_META& meta, TSK_FS_TYPE_ENUM fsType) {
  jsoncons::json jsMeta(
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
      { "attrs", convertAttrs(meta) }
    }
  );

  convertTimestamps(meta, fsType, jsMeta);

  return jsMeta;
}

void TskConverter::convertNTFSTimestamps(const TSK_FS_META& meta, jsoncons::json& ts) {
  ts["deleted"] = jsoncons::null_type();
  ts["backup"] = jsoncons::null_type();
  ts["fn_accessed"] = formatTimestamp(meta.time2.ntfs.fn_atime, meta.time2.ntfs.fn_atime_nano);
  ts["fn_created"] = formatTimestamp(meta.time2.ntfs.fn_crtime, meta.time2.ntfs.fn_crtime_nano);
  ts["fn_metadata"] = formatTimestamp(meta.time2.ntfs.fn_ctime, meta.time2.ntfs.fn_ctime_nano);
  ts["fn_modified"] = formatTimestamp(meta.time2.ntfs.fn_mtime, meta.time2.ntfs.fn_mtime_nano);
}

void TskConverter::convertEXTTimestamps(const TSK_FS_META& meta, jsoncons::json& ts) {
  ts["deleted"] = formatTimestamp(meta.time2.hfs.bkup_time, meta.time2.hfs.bkup_time_nano);
  ts["backup"] = jsoncons::null_type();
  ts["fn_accessed"] = jsoncons::null_type();
  ts["fn_created"] = jsoncons::null_type();
  ts["fn_metadata"] = jsoncons::null_type();
  ts["fn_modified"] = jsoncons::null_type();
}

void TskConverter::convertHFSTimestamps(const TSK_FS_META& meta, jsoncons::json& ts) {
  ts["deleted"] = jsoncons::null_type();
  ts["backup"] = formatTimestamp(meta.time2.hfs.bkup_time, meta.time2.hfs.bkup_time_nano);
  ts["fn_accessed"] = jsoncons::null_type();
  ts["fn_created"] = jsoncons::null_type();
  ts["fn_metadata"] = jsoncons::null_type();
  ts["fn_modified"] = jsoncons::null_type();
}

void TskConverter::convertDefaultTimestamps(const TSK_FS_META& /* meta */, jsoncons::json& ts) const {
  ts["deleted"] = jsoncons::null_type();
  ts["backup"] = jsoncons::null_type();
  ts["fn_accessed"] = jsoncons::null_type();
  ts["fn_created"] = jsoncons::null_type();
  ts["fn_metadata"] = jsoncons::null_type();
  ts["fn_modified"] = jsoncons::null_type();
}

void TskConverter::convertStandardTimestamps(const TSK_FS_META& meta, jsoncons::json& ts) {
  ts["accessed"] = formatTimestamp(meta.atime, meta.atime_nano);
  ts["created"] = formatTimestamp(meta.crtime, meta.crtime_nano);
  ts["metadata"] = formatTimestamp(meta.ctime, meta.ctime_nano);
  ts["modified"] = formatTimestamp(meta.mtime, meta.mtime_nano);
}

void TskConverter::convertTimestamps(const TSK_FS_META& meta, TSK_FS_TYPE_ENUM fsType, jsoncons::json& ts) {
  convertStandardTimestamps(meta, ts);

  switch (fsType) {
    case TSK_FS_TYPE_NTFS:
      convertNTFSTimestamps(meta, ts);
      break;
    case TSK_FS_TYPE_FFS1: // need to double-check this list
    case TSK_FS_TYPE_FFS1B:
    case TSK_FS_TYPE_FFS2:
    case TSK_FS_TYPE_EXT2:
    case TSK_FS_TYPE_EXT3:
    case TSK_FS_TYPE_EXT4:
      convertEXTTimestamps(meta, ts);
      break;
    case TSK_FS_TYPE_HFS:
      convertHFSTimestamps(meta, ts);
      break;
    default:
      convertDefaultTimestamps(meta, ts);
      break;
  }
}

jsoncons::json TskConverter::formatTimestamp(int64_t unix_time, uint32_t ns) {
  std::string ret;

  if (0 == unix_time) {
    if (0 == ns) {
      return jsoncons::null_type();
    }
    // some C libs will otherwise print an empty string with strftime
    ret.append("1970-01-01 00:00:00");
  }
  else {
    // Boost, you tried.
    //const boost::posix_time::ptime pt = boost::posix_time::from_time_t(unix_time);
    try {
      const boost::posix_time::ptime start(boost::gregorian::date(1970, 1, 1));
      const int64_t min = unix_time / 60;
      // Boost Date-Time has a maximum year of around 10000,
      // Which means the number of _hours_ since 1970 will fit in a int32_t
      // (In some versions of Boost (1_64), the time_duration takes an int32_t hours param,
      //  While in others it takes a std::time_t hours)
      boost::posix_time::time_duration duration(
        static_cast<boost::posix_time::time_res_traits::hour_type>(min / 60),
        static_cast<boost::posix_time::time_res_traits::min_type>(min  % 60),
        static_cast<boost::posix_time::time_res_traits::sec_type>(unix_time % 60)
      );
      const boost::posix_time::ptime pt = start + duration;
      const tm pt_tm = boost::posix_time::to_tm(pt);
      char tbuf[100];
      const size_t len = strftime(tbuf, 100, "%Y-%m-%d %H:%M:%S", &pt_tm);
      if (len) {
        ret.append(tbuf);
      } // else error??? [a greybeard once said, do not test for errors you can't handle... -- jls]
    }
    catch (const std::exception&) {
      // FIXME: Under what conditions can this happen? Should we clear ret
      // if it does?
    }
  }

  // fractional seconds
  if (ns - 1 < 999999999) {
    NanoBuf << double(ns) / 1000000000;
    auto frac = NanoBuf.str();
    ret.append(frac.substr(1, frac.find_last_not_of('0'))); // no leading or trailing zeroes
    NanoBuf.str("");
  }
  return ret;
}

std::string TskUtils::extractString(const char* str, unsigned int size) {
  return std::string(str, std::find(str, str + size, '\0'));
}

jsoncons::json TskConverter::convertAttr(const TSK_FS_ATTR& attr) const {
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

      nrd_runs.push_back(convertNRDR(*i));
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

jsoncons::json TskConverter::convertNRDR(const TSK_FS_ATTR_RUN& dataRun) const {
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
