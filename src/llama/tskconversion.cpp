#include "tskconversion.h"

#include <algorithm>
#include <array>

#include <boost/date_time/posix_time/posix_time.hpp>

TskConverter::TskConverter()
{
  NanoBuf << std::fixed << std::setprecision(9);
}

template <class F>
std::string flagsString(unsigned int flags, const F& fmap) {
  if (!flags) {
    return "";
  }

  std::string ret;
  bool first = true;
  for (const auto& f: fmap) {
    if (flags & f.first) {
      if (first) {
        first = false;
      }
      else {
        ret += ", ";
      }
      ret += f.second;
    }
  }

  return ret;
}

std::string TskConverter::volumeSystemType(unsigned int type) const {
  switch (type) {
  case TSK_VS_TYPE_DOS:
    return "MBR";
  case TSK_VS_TYPE_BSD:
    return "BSD";
  case TSK_VS_TYPE_SUN:
    return "Sun";
  case TSK_VS_TYPE_MAC:
    return "Macintosh";
  case TSK_VS_TYPE_GPT:
    return "GPT";
  default:
    return "Unknown";
  }
}

std::string TskConverter::volumeFlags(unsigned int flags) const {
  // I think these flags are mutually exclusive...
  switch (flags) {
  case TSK_VS_PART_FLAG_ALLOC:
    return "Allocated";
  case TSK_VS_PART_FLAG_UNALLOC:
    return "Unallocated";
  case TSK_VS_PART_FLAG_META:
    return "Volume System";
  default:
    return "";
  }
}

std::string TskConverter::filesystemFlags(unsigned int flags) const {
  // this structure obviously won't scale as more flags are added
  // but it's fine for now
  switch (flags) {
  case TSK_FS_INFO_FLAG_HAVE_SEQ:
    return "Sequenced";
  case TSK_FS_INFO_FLAG_HAVE_NANOSEC:
    return "Nanosecond precision";
  case TSK_FS_INFO_FLAG_HAVE_SEQ | TSK_FS_INFO_FLAG_HAVE_NANOSEC:
    return "Sequenced, Nanosecond precision";
  default:
    return "";
  }
}

std::string TskConverter::nameType(unsigned int type) const {
// FIXME: use the enum?
  static const std::array<std::string, 12> types{{
    "Undefined",
    "Named Pipe",
    "Character Device",
    "Folder",
    "Block Device",
    "File",
    "Symbolic Link",
    "Domain Socket",
    "Shadow Inode",
    "Whiteout Inode",
    "Virtual",
    "Virtual Folder"
  }};
  return type < types.size() ? types[type]: types[0];
}

std::string TskConverter::nameFlags(unsigned int flags) const {
  const static std::array<std::pair<unsigned int, std::string>, 2> fmap{{
    {TSK_FS_NAME_FLAG_ALLOC,   "Allocated"},
    {TSK_FS_NAME_FLAG_UNALLOC, "Deleted"}
  }};
  return flagsString(flags, fmap);
}

std::string TskConverter::metaType(unsigned int type) const {
  static const std::array<std::string, 12> types{
    "Undefined",
    "File",
    "Folder",
    "Named Pipe",
    "Character Device",
    "Block Device",
    "Symbolic Link",
    "Shadow Inode",
    "Domain Socket",
    "Whiteout Inode",
    "Virtual",
    "Virtual Folder"
  };
  return type < types.size() ? types[type]: types[0];
}

std::string TskConverter::metaFlags(unsigned int flags) const {
  const static std::array<std::pair<unsigned int, std::string>, 6> fmap{{
    {TSK_FS_META_FLAG_ALLOC,   "Allocated"},
    {TSK_FS_META_FLAG_UNALLOC, "Deleted"},
    {TSK_FS_META_FLAG_USED,    "Used"},
    {TSK_FS_META_FLAG_UNUSED,  "Unused"},
    {TSK_FS_META_FLAG_COMP,    "Compressed"},
    {TSK_FS_META_FLAG_ORPHAN,  "Orphan"}
  }};
  return flagsString(flags, fmap);
}

std::string TskConverter::attrType(unsigned int type) const {
  switch (type) {
  case TSK_FS_ATTR_TYPE_NOT_FOUND: return "Unknown";
  case TSK_FS_ATTR_TYPE_DEFAULT: return "Data"; // default _is_ data, so match up with NTFS Data
  case TSK_FS_ATTR_TYPE_NTFS_SI: return "Standard Information";
  case TSK_FS_ATTR_TYPE_NTFS_ATTRLIST: return "NTFS Attributes";
  case TSK_FS_ATTR_TYPE_NTFS_FNAME: return "Filename";
  case TSK_FS_ATTR_TYPE_NTFS_OBJID: return "ObjID";
  case TSK_FS_ATTR_TYPE_NTFS_SEC: return "Sec";
  case TSK_FS_ATTR_TYPE_NTFS_VNAME: return "VName";
  case TSK_FS_ATTR_TYPE_NTFS_VINFO: return "VInfo";
  case TSK_FS_ATTR_TYPE_NTFS_DATA: return "Data";
  case TSK_FS_ATTR_TYPE_NTFS_IDXROOT: return "IdxRoot";
  case TSK_FS_ATTR_TYPE_NTFS_IDXALLOC: return "IdxAlloc";
  case TSK_FS_ATTR_TYPE_NTFS_BITMAP: return "Bitmap";
  case TSK_FS_ATTR_TYPE_NTFS_SYMLNK: return "Symlink";
  // Reparse points are a Win2K feature and use the same type code as symlink.
  // So this is technically ambiguous. To bite the bullet, we go with symlinks.
//  case TSK_FS_ATTR_TYPE_NTFS_REPARSE: return "Reparse";
  case TSK_FS_ATTR_TYPE_NTFS_EAINFO: return "EAInfo";
  case TSK_FS_ATTR_TYPE_NTFS_EA: return "EA";
  case TSK_FS_ATTR_TYPE_NTFS_PROP: return "Prop";
  case TSK_FS_ATTR_TYPE_NTFS_LOG: return "Log";

  case TSK_FS_ATTR_TYPE_UNIX_INDIR: return "Indirect";
  case TSK_FS_ATTR_TYPE_UNIX_EXTENT: return "Extents";

  // Types for HFS+ File Attributes
//  case TSK_FS_ATTR_TYPE_HFS_DEFAULT: return "Data"; // same value as DEFAULT above
  case TSK_FS_ATTR_TYPE_HFS_DATA: return "Data";
  case TSK_FS_ATTR_TYPE_HFS_RSRC: return "Resource";
  case TSK_FS_ATTR_TYPE_HFS_EXT_ATTR: return "EA";
  case TSK_FS_ATTR_TYPE_HFS_COMP_REC: return "Compressed";
  default:
    return "Unknown";
  }
}

std::string TskConverter::attrFlags(unsigned int flags) const {
  static std::array<std::pair<unsigned int, std::string>, 7> fmap{{
    {TSK_FS_ATTR_INUSE,   "In Use"},
    {TSK_FS_ATTR_NONRES, "Non-resident"},
    {TSK_FS_ATTR_RES, "Resident"},
    {TSK_FS_ATTR_ENC, "Encrypted"},
    {TSK_FS_ATTR_COMP, "Compressed"},
    {TSK_FS_ATTR_SPARSE, "Sparse"},
    {TSK_FS_ATTR_RECOVERY, "Recovered"}
  }};
  return flagsString(flags, fmap);
}

std::string TskConverter::nrdRunFlags(unsigned int flags) const {
  switch (flags) {
  case TSK_FS_ATTR_RUN_FLAG_NONE: return "";
  case TSK_FS_ATTR_RUN_FLAG_FILLER: return "Filler";
  case TSK_FS_ATTR_RUN_FLAG_SPARSE: return "Sparse";
  }
  return "";
}

void TskConverter::convertFile(const TSK_FS_FILE& file, jsoncons::json& jsFile) {
  if (file.name) {
    auto& jsName = (jsFile["name"] = jsoncons::json());
    convertName(*file.name, jsName);
  }

  // TODO: do we need to call convertMeta here?

}

void TskConverter::convertName(const TSK_FS_NAME& name, jsoncons::json& jsName) const {
  jsName["name"] = name.name;
  jsName["shrt_name"] = name.shrt_name;
  jsName["meta_addr"] = std::to_string(name.meta_addr);
  jsName["meta_seq"] = std::to_string(name.meta_seq);
  jsName["par_addr"] = std::to_string(name.par_addr);
  jsName["par_seq"] = std::to_string(name.par_seq);
//  jsName["date_added"] = name.date_added;
  jsName["type"] = nameType(name.type);
  jsName["flags"] = nameFlags(name.flags);
}

void TskConverter::convertMeta(const TSK_FS_META& meta, TSK_FS_TYPE_ENUM fsType, jsoncons::json& jsMeta) {
  jsMeta["addr"] = meta.addr;
  jsMeta["flags"] = metaFlags(meta.flags);
  jsMeta["type"] = metaType(meta.type);

  jsMeta["uid"] = std::to_string(meta.uid);
  jsMeta["gid"] = std::to_string(meta.gid);

  jsMeta["link"] = meta.link ? meta.link : "";
  jsMeta["nlink"] = meta.nlink;

  jsMeta["seq"] = meta.seq;

  convertTimestamps(meta, fsType, jsMeta);

  if (meta.attr) {
    auto& jsAttrs = (jsMeta["attrs"] = jsoncons::json::make_array());
    for (TSK_FS_ATTR* itr = meta.attr->head; itr; itr = itr->next) {
      convertAttr(*itr, jsAttrs.emplace_back());
    }
  }
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

std::string TskConverter::extractString(const char* str, unsigned int size) const {
  return std::string(str, std::find(str, str + size, '\0'));
}

void TskConverter::convertAttr(const TSK_FS_ATTR& attr, jsoncons::json& jsAttr) const {
  jsAttr["id"] = attr.id;
  jsAttr["flags"] = attrFlags(attr.flags);
  jsAttr["name"] = extractString(attr.name, attr.name_size);
  jsAttr["size"] = attr.size;
  jsAttr["type"] = attrType(attr.type);
  if (attr.flags & TSK_FS_ATTR_RES) {
    jsAttr["rd_buf"] = hexEncode(attr.rd.buf, std::min(attr.size, static_cast<int64_t>(attr.rd.buf_size)));
    jsAttr["rd_offset"] = attr.rd.offset;
  }
  else { // non-resident
    jsAttr["nrd_allocsize"] = attr.nrd.allocsize;
    jsAttr["nrd_compsize"] = attr.nrd.compsize;
    jsAttr["nrd_initsize"] = attr.nrd.initsize;
    jsAttr["nrd_skiplen"] = attr.nrd.skiplen;
    auto& nrd_runs = (jsAttr["nrd_runs"] = jsoncons::json::make_array());
    // size_t i = 0;
    for (auto itr = attr.nrd.run; itr; itr = itr->next) {
      convertNRDR(*itr, nrd_runs.emplace_back());
      if (itr == attr.nrd.run_end) {
        // this is hopefully unnecessary, but what if
        // attr.nrd.run_end.next isn't null?
        // paranoia is a feature
        break;
      }
    }
  }
}

void TskConverter::convertNRDR(const TSK_FS_ATTR_RUN& dataRun, jsoncons::json& nrdr) const {
  nrdr["addr"]   = dataRun.addr;
  nrdr["flags"]  = nrdRunFlags(dataRun.flags);
  nrdr["len"]    = dataRun.len;
  nrdr["offset"] = dataRun.offset;
}

// Provide these temporarily until we have sfhash_hex in libhasher
template <typename C>
void to_hex(char* dst, C beg, C end) {
  static constexpr char hex[] {
    '0', '1', '2', '3', '4', '5', '6', '7',
    '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'
  };

  for (C c = beg; c != end; ++c) {
    const uint8_t lo = *c & 0x0F;
    const uint8_t hi = *c >> 4;

    *dst++ = hex[hi];
    *dst++ = hex[lo];
  }
}

void to_hex(char* dst, const void* src, size_t slen) {
  to_hex(dst, static_cast<const uint8_t*>(src),
              static_cast<const uint8_t*>(src) + slen);
}

void sfhash_hex(char* dst, const void* src, size_t len) {
  to_hex(dst, static_cast<const uint8_t*>(src),
              static_cast<const uint8_t*>(src) + len);
}

std::string hexString(const void* str, unsigned int size) {
  std::string ret(2 * size, '\0');
  sfhash_hex(&ret[0], str, size);
  return ret;
}

std::string TskConverter::hexEncode(const void* str, unsigned int size) const {
  return hexString(str, size);
}
