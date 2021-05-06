#include "dirconversion.h"

#include "schema.h"

#include <system_error>

namespace fs = std::filesystem;

std::string DirUtils::fileTypeString(fs::file_type type) {
  switch (type) {
  case fs::file_type::none:
  case fs::file_type::not_found:
    return TYPE_UNDEF;
  case fs::file_type::regular:
    return TYPE_REG;
  case fs::file_type::directory:
    return TYPE_DIR;
  case fs::file_type::symlink:
    return TYPE_LNK;
  case fs::file_type::block:
    return TYPE_BLK;
  case fs::file_type::character:
    return TYPE_CHR;
  case fs::file_type::fifo:
    return TYPE_FIFO;
  case fs::file_type::socket:
    return TYPE_SOCK;
  case fs::file_type::unknown:
  default:
    return TYPE_UNDEF;
  }
}

fs::file_type DirUtils::fileType(const fs::directory_entry& de) {
  std::error_code err;
  const fs::file_status status = de.symlink_status(err);
  if (err) {
    std::cerr << "Error: " << de.path() << ": " << err.message() << std::endl;
    return fs::file_type::unknown;
  }

  return status.type();
}

std::uintmax_t DirUtils::nlink(const fs::directory_entry& de) {
  std::error_code err;
  const auto c = de.hard_link_count(err);
  if (err) {
    std::cerr << "Error: " << de.path() << ": " << err.message() << std::endl;
    return 0;
  }

  return c;
}

std::uintmax_t DirUtils::fileSize(const fs::directory_entry& de) {
  std::error_code err;
  const auto c = de.file_size(err);
  if (err) {
    if (err == std::errc::is_a_directory) {
      // ignore
    }
    else {
      std::cerr << "Error: " << de.path() << ": " << err.message() << std::endl;
    }
    return 0;
  }

  return c;
}

/*
fs::file_time_type DirUtils::mtime(const fs::directory_entry& de) {
  std::error_code err;
  const auto m = de.last_write_time(err);
  if (err) {
    std::cerr << "Error: " << err.message() << std::endl;
    return 0;
  }

  return m;
}
*/

jsoncons::json DirConverter::convertMeta(const fs::directory_entry& de) const {
  static const std::string flags = std::string(META_FLAG_ALLOC) + ", " + META_FLAG_USED;

  return jsoncons::json(
    jsoncons::json_object_arg,
    {
      { "addr",        jsoncons::null_type() },
      { "flags",       flags },
      { "type",        DirUtils::fileTypeString(DirUtils::fileType(de)) },
      { "uid",         jsoncons::null_type() },
      { "gid",         jsoncons::null_type() },
      { "link",        "" },
      { "nlink",       DirUtils::nlink(de) },
      { "seq",         jsoncons::null_type() },
      { "attrs",       convertAttrs(de) },
      { "accessed",    jsoncons::null_type() },
      { "created",     jsoncons::null_type() },
      { "metadata",    jsoncons::null_type() },
//      { "modified",    DirUtils::mtime(de) },
      { "modified",    jsoncons::null_type() },
      { "deleted",     jsoncons::null_type() },
      { "backup",      jsoncons::null_type() },
      { "fn_accessed", jsoncons::null_type() },
      { "fn_created",  jsoncons::null_type() },
      { "fn_metadata", jsoncons::null_type() },
      { "fn_modified", jsoncons::null_type() }
    }
  );
}

jsoncons::json DirConverter::convertAttrs(const fs::directory_entry& de) const {
  return jsoncons::json(
    jsoncons::json_array_arg,
    {
      convertAttr(de)
    }
  );
}

jsoncons::json DirConverter::convertAttr(const fs::directory_entry& de) const {
  static const std::string flags = std::string(ATTR_FLAG_INUSE) + ", " + ATTR_FLAG_NONRES;

  return jsoncons::json(
    jsoncons::json_object_arg,
    {
      { "id",            jsoncons::null_type() },
      { "flags",         flags },
      { "name",          jsoncons::null_type() },
      { "nrd_allocsize", DirUtils::fileSize(de) },
      { "type",          ATTR_TYPE_UNKNOWN }
    }
  );
}

jsoncons::json DirConverter::convertName(const fs::directory_entry& de) const {
  return jsoncons::json(
    jsoncons::json_object_arg,
    {
      { "name", de.path().filename().generic_string() },
      { "shrt_name", jsoncons::null_type() },
      { "meta_addr", jsoncons::null_type() },
      { "meta_seq",  jsoncons::null_type() },
      { "par_addr",  jsoncons::null_type() },
      { "par_seq",   jsoncons::null_type() },
//      { "date_added", name.date_added },
      { "type",      DirUtils::fileTypeString(DirUtils::fileType(de)) },
      { "flags",     NAME_FLAG_ALLOC }
    }
  );
}
