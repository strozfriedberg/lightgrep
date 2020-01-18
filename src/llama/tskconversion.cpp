#include "tskconversion.h"

#include <array>

#include <boost/date_time/posix_time/posix_time.hpp>

TskConverter::TskConverter()
{
  NanoBuf << std::fixed << std::setprecision(9);
}

std::string TskConverter::volumeSystemType(unsigned int type) {
  std::string ret = "Unknown";
  switch (type) {
  case TSK_VS_TYPE_DOS:
    ret = "MBR";
    break;
  case TSK_VS_TYPE_BSD:
    ret = "BSD";
    break;
  case TSK_VS_TYPE_SUN:
    ret = "Sun";
    break;
  case TSK_VS_TYPE_MAC:
    ret = "Macintosh";
    break;
  case TSK_VS_TYPE_GPT:
    ret = "GPT";
    break;
  }
  return ret;
}

std::string TskConverter::volumeFlags(unsigned int flags) {
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

std::string TskConverter::filesystemFlags(unsigned int flags) {
  // this structure obviously won't scale as more flags are added
  // but it's fine for now
  switch (flags) {
  case TSK_FS_INFO_FLAG_HAVE_SEQ:
    return "Sequenced";
  case TSK_FS_INFO_FLAG_HAVE_NANOSEC:
    return "Nanosecond precision";
  case TSK_FS_INFO_FLAG_HAVE_SEQ | TSK_FS_INFO_FLAG_HAVE_NANOSEC:
    return "Sequenced, Nanosecond precision";
  }
  return "";
}

std::string TskConverter::nameType(unsigned int type) {
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

std::string TskConverter::nameFlags(unsigned int flags) {
  std::string ret;
  if (flags) {
    bool has = false;
    std::ostringstream buf;
    if (flags & TSK_FS_NAME_FLAG_ALLOC) {
      buf << "Allocated";
      has = true;
    }
    if (flags & TSK_FS_NAME_FLAG_UNALLOC) {
      if (has) {
        buf << ", ";
      }
      buf << "Deleted";
      has = true;
    }
    ret = buf.str();
  }
  return ret;
}

std::string TskConverter::metaType(unsigned int type) {
  static const std::array<std::string, 12> types{{
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
  }};
  return type < types.size() ? types[type]: types[0];
}

std::string TskConverter::metaFlags(unsigned int flags) {
  std::string ret;
  if (flags) {
    bool has = false;
    std::ostringstream buf;
    if (flags & TSK_FS_META_FLAG_ALLOC) {
      buf << "Allocated";
      has = true;
    }
    if (flags & TSK_FS_META_FLAG_UNALLOC) {
      if (has) {
        buf << ", ";
      }
      buf << "Deleted";
      has = true;
    }
    if (flags & TSK_FS_META_FLAG_USED) {
      if (has) {
        buf << ", ";
      }
      buf << "Used";
      has = true;
    }
    if (flags & TSK_FS_META_FLAG_UNUSED) {
      if (has) {
        buf << ", ";
      }
      buf << "Unused";
      has = true;
    }
    if (flags & TSK_FS_META_FLAG_COMP) {
      if (has) {
        buf << ", ";
      }
      buf << "Compressed";
      has = true;
    }
    if (flags & TSK_FS_META_FLAG_ORPHAN) {
      if (has) {
        buf << ", ";
      }
      buf << "Orphan";
      has = true;
    }
    ret = buf.str();
  }
  return ret;
}

std::string TskConverter::attrType(unsigned int type) {
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

std::string TskConverter::attrFlags(unsigned int flags) {
  std::string ret;
  if (flags) {
    bool has = false;
    std::ostringstream buf;
    if (flags & TSK_FS_ATTR_INUSE) {
      buf << "In Use";
      has = true;
    }
    if (flags & TSK_FS_ATTR_NONRES) {
      if (has) {
        buf << ", ";
      }
      buf << "Non-resident";
      has = true;
    }
    if (flags & TSK_FS_ATTR_RES) {
      if (has) {
        buf << ", ";
      }
      buf << "Resident";
      has = true;
    }
    if (flags & TSK_FS_ATTR_ENC) {
      if (has) {
        buf << ", ";
      }
      buf << "Encrypted";
      has = true;
    }
    if (flags & TSK_FS_ATTR_COMP) {
      if (has) {
        buf << ", ";
      }
      buf << "Compressed";
      has = true;
    }
    if (flags & TSK_FS_ATTR_SPARSE) {
      if (has) {
        buf << ", ";
      }
      buf << "Sparse";
      has = true;
    }
    if (flags & TSK_FS_ATTR_RECOVERY) {
      if (has) {
        buf << ", ";
      }
      buf << "Recovered";
      has = true;
    }
    ret = buf.str();
  }
  return ret;
}

std::string TskConverter::nrdRunFlags(unsigned int flags) {
  switch (flags) {
  case TSK_FS_ATTR_RUN_FLAG_NONE: return "";
  case TSK_FS_ATTR_RUN_FLAG_FILLER: return "Filler";
  case TSK_FS_ATTR_RUN_FLAG_SPARSE: return "Sparse";
  }
  return "";
}

void TskConverter::convertTimestamps(const TSK_FS_META& meta, TSK_FS_TYPE_ENUM fsType, jsoncons::json& timestamps) {
  timestamps["accessed"] = formatTimestamp(meta.atime, meta.atime_nano);
  timestamps["created"] = formatTimestamp(meta.crtime, meta.crtime_nano);
  timestamps["metadata"] = formatTimestamp(meta.ctime, meta.ctime_nano);
  timestamps["modified"] = formatTimestamp(meta.mtime, meta.mtime_nano);

  switch (fsType) {
    case TSK_FS_TYPE_NTFS:
      timestamps["deleted"] = jsoncons::null_type();
      timestamps["backup"] = jsoncons::null_type();
      timestamps["fn_accessed"] = formatTimestamp(meta.time2.ntfs.fn_atime, meta.time2.ntfs.fn_atime_nano);
      timestamps["fn_created"] = formatTimestamp(meta.time2.ntfs.fn_crtime, meta.time2.ntfs.fn_crtime_nano);
      timestamps["fn_metadata"] = formatTimestamp(meta.time2.ntfs.fn_ctime, meta.time2.ntfs.fn_ctime_nano);
      timestamps["fn_modified"] = formatTimestamp(meta.time2.ntfs.fn_mtime, meta.time2.ntfs.fn_mtime_nano);
      break;
    case TSK_FS_TYPE_FFS1: // need to double-check this list
    case TSK_FS_TYPE_FFS1B:
    case TSK_FS_TYPE_FFS2:
    case TSK_FS_TYPE_EXT2:
    case TSK_FS_TYPE_EXT3:
    case TSK_FS_TYPE_EXT4:
      timestamps["deleted"] = formatTimestamp(meta.time2.hfs.bkup_time, meta.time2.hfs.bkup_time_nano);
      timestamps["backup"] = jsoncons::null_type();
      timestamps["fn_accessed"] = jsoncons::null_type();
      timestamps["fn_created"] = jsoncons::null_type();
      timestamps["fn_metadata"] = jsoncons::null_type();
      timestamps["fn_modified"] = jsoncons::null_type();
      break;    
    case TSK_FS_TYPE_HFS:
      timestamps["deleted"] = jsoncons::null_type();
      timestamps["backup"] = formatTimestamp(meta.time2.hfs.bkup_time, meta.time2.hfs.bkup_time_nano);
      timestamps["fn_accessed"] = jsoncons::null_type();
      timestamps["fn_created"] = jsoncons::null_type();
      timestamps["fn_metadata"] = jsoncons::null_type();
      timestamps["fn_modified"] = jsoncons::null_type();
      break;
    default:
      timestamps["deleted"] = jsoncons::null_type();
      timestamps["backup"] = jsoncons::null_type();
      timestamps["fn_accessed"] = jsoncons::null_type();
      timestamps["fn_created"] = jsoncons::null_type();
      timestamps["fn_metadata"] = jsoncons::null_type();
      timestamps["fn_modified"] = jsoncons::null_type();
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
    } catch (std::exception&) {}
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

void TskConverter::convertNRDR(const TSK_FS_ATTR_RUN& dataRun, jsoncons::json& nrdr) {
  nrdr["addr"]   = dataRun.addr;
  nrdr["flags"]  = nrdRunFlags(dataRun.flags);
  nrdr["len"]    = dataRun.len;
  nrdr["offset"] = dataRun.offset;
}
