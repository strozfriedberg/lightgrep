#include "outputtar.h"

#include "filerecord.h"

#include <iostream>

#include <archive.h>
#include <archive_entry.h>

void closeAndFreeArchive(archive* a) {
  archive_write_close(a);
  archive_write_free(a);
}

OutputTar::OutputTar(const std::string& path, Options::Codecs codec):
  Path(path),
  Archive(archive_write_new(), closeAndFreeArchive)
{
  std::string ext = ".tar";
  switch (codec) {
  case Options::CODEC_NONE:
    break;
  case Options::CODEC_GZIP:
    ext += ".gz";
    archive_write_add_filter_gzip(Archive.get());
    break;
  case Options::CODEC_LZ4:
    ext += ".lz4";
    archive_write_add_filter_lz4(Archive.get());
    break;
  case Options::CODEC_LZMA:
    ext += ".lzma";
    archive_write_add_filter_lzma(Archive.get());
    break;
  case Options::CODEC_BZIP2:
    ext += ".bz2";
    archive_write_add_filter_bzip2(Archive.get());
    break;
  case Options::CODEC_LZOP:
    ext += ".lzo";
    archive_write_add_filter_lzop(Archive.get());
    break;
  case Options::CODEC_XZ:
    ext += ".xz";
    archive_write_add_filter_xz(Archive.get());
    break;
  }

  Path.append(ext);
  archive_write_set_format_pax_restricted(Archive.get());
  archive_write_open_filename(Archive.get(), Path.c_str());
}

void OutputTar::outputFile(const FileRecord& rec) {
  // std::cerr << "Adding " << rec.Path << " to output tarball" << std::endl;
  std::shared_ptr<archive_entry> entry(archive_entry_new(), archive_entry_free);

  archive_entry_set_pathname(entry.get(), rec.Path.c_str());
  archive_entry_set_size(entry.get(), rec.Size);
  archive_entry_set_filetype(entry.get(), AE_IFREG);
  archive_entry_set_perm(entry.get(), 0644);
  archive_write_header(Archive.get(), entry.get());

  archive_write_data(Archive.get(), rec._data.c_str(), rec._data.size());
}
