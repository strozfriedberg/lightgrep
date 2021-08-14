#include "outputtar.h"

#include "outputchunk.h"
#include "util.h"

#include <ctime>
#include <iostream>

#include <archive.h>
#include <archive_entry.h>

void closeAndFreeArchive(archive* a) {
  archive_write_close(a);
  archive_write_free(a);
}

OutputTar::OutputTar(const std::string& path, Codec codec):
  Path(path),
  Archive(archive_write_new(), closeAndFreeArchive)
{
  std::string ext = ".tar";
  switch (codec) {
  case Codec::NONE:
    break;
  case Codec::GZIP:
    ext += ".gz";
    archive_write_add_filter_gzip(Archive.get());
    break;
  case Codec::LZ4:
    ext += ".lz4";
    archive_write_add_filter_lz4(Archive.get());
    break;
  case Codec::LZMA:
    ext += ".lzma";
    archive_write_add_filter_lzma(Archive.get());
    break;
  case Codec::BZIP2:
    ext += ".bz2";
    archive_write_add_filter_bzip2(Archive.get());
    break;
  case Codec::LZOP:
    ext += ".lzo";
    archive_write_add_filter_lzop(Archive.get());
    break;
  case Codec::XZ:
    ext += ".xz";
    archive_write_add_filter_xz(Archive.get());
    break;
  }

  Path.append(ext);
  archive_write_set_format_pax_restricted(Archive.get());
  archive_write_open_filename(Archive.get(), Path.c_str());
}

void OutputTar::doOutput(const char* path, const char* data, size_t len) {
  // std::cerr << "Adding " << path << " to output tarball" << std::endl;
  auto entry = make_unique_del(archive_entry_new(), archive_entry_free);

  archive_entry_set_pathname(entry.get(), path);
  archive_entry_set_size(entry.get(), len);
  archive_entry_set_filetype(entry.get(), AE_IFREG);
  archive_entry_set_perm(entry.get(), 0644);
  archive_entry_set_mtime(entry.get(), std::time(nullptr), 0);
  archive_write_header(Archive.get(), entry.get());
  archive_write_data(Archive.get(), data, len);
}

void OutputTar::doOutput(const OutputChunk& c) {
  doOutput(c.path.c_str(), c.data.c_str(), c.data.size());
}

void OutputTar::outputImage(const OutputChunk& c) {
  doOutput(c);
}

void OutputTar::outputDirent(const OutputChunk& c) {
  doOutput(c);
}

void OutputTar::outputInode(const OutputChunk& c) {
  doOutput(c);
}
