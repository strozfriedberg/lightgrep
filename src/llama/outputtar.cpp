#include "outputbase.h"

#include <iostream>
#include <memory>

#include <archive.h>
#include <archive_entry.h>

#include "boost_asio.h"
#include "filerecord.h"
#include "options.h"
#include "recordbuffer.h"

void closeAndFreeArchive(archive *a) {
  archive_write_close(a);
  archive_write_free(a);
}

class OutputTar : public OutputBase {
public:
  OutputTar(boost::asio::thread_pool &pool, const std::string &path, Options::Codecs codec);

  virtual ~OutputTar() {
    close();
  }

  virtual void outputFile(const FileRecord &rec) override {
    // std::cerr << "OutputTar::outputFile: " << rec.Path << std::endl;
    if (Closed) {
      // we might still have some records in FileRecBuf, but the 
      // threadpool has gone away and the MainStrand can no longer be
      // posted to, so just call into the function directly.
      writeFileRecord(rec);
    }
    else {
      boost::asio::post(MainStrand, [=](){ writeFileRecord(rec); });      
    }
  }

  virtual void outputRecord(const FileRecord &rec) override {
    boost::asio::post(RecStrand, [=]() { FileRecBuf.write(rec.str()); });
  }

  virtual void outputRecords(const std::shared_ptr<std::vector<FileRecord>>& batch) override {
    boost::asio::post(RecStrand, [=]() {
      for (auto& rec: *batch) {
        // std::cerr << "Writing " << rec.str() << std::endl;
        FileRecBuf.write(rec.str());
        // FileRecBuf.get() << rec.Doc << '\n';
      }
    });
  }

  virtual void outputSearchHit(const std::string &) override {}

  virtual void close() override {
    Closed = true; // FileRecBuf's destructor will take care of final flush
  }

private:
  void writeFileRecord(const FileRecord &rec);

  boost::asio::strand<boost::asio::thread_pool::executor_type> MainStrand,
                                                               RecStrand;

  std::string Path;

  std::shared_ptr<archive> Archive;

  RecordBuffer FileRecBuf; // must be destroyed before Archive

  bool Closed;
};

std::shared_ptr<OutputBase>
OutputBase::createTarWriter(boost::asio::thread_pool &pool,
                            const std::string &path,
                            Options::Codecs codec)
{
  return std::static_pointer_cast<OutputBase>(
      std::shared_ptr<OutputTar>(new OutputTar(pool, path, codec)));
}

OutputTar::OutputTar(boost::asio::thread_pool &pool, const std::string &path, Options::Codecs codec)
    : MainStrand(pool.get_executor()), RecStrand(pool.get_executor()),
      Path(path), Archive(archive_write_new(), closeAndFreeArchive),
      FileRecBuf("recs/file_recs", 16 * 1024 * 1024, *this),
      Closed(false)
{
  std::string ext;
  switch (codec) {
    case Options::CODEC_NONE:
      ext = ".tar";
      break;
    case Options::CODEC_GZIP:
      ext = ".tar.gz";
      archive_write_add_filter_gzip(Archive.get());
      break;
    case Options::CODEC_LZ4:
      ext = ".tar.lz4";
      archive_write_add_filter_lz4(Archive.get());
      break;
  }
  Path.append(ext);
  archive_write_set_format_pax_restricted(Archive.get());
  archive_write_open_filename(Archive.get(), Path.c_str());
}

void OutputTar::writeFileRecord(const FileRecord &rec) {
  // std::cerr << "Adding " << rec.Path << " to output tarball" << std::endl;
  std::shared_ptr<archive_entry> entry(archive_entry_new(), archive_entry_free);

  archive_entry_set_pathname(entry.get(), rec.Path.c_str());
  archive_entry_set_size(entry.get(), rec.Size);
  archive_entry_set_filetype(entry.get(), AE_IFREG);
  archive_entry_set_perm(entry.get(), 0644);
  archive_write_header(Archive.get(), entry.get());

  archive_write_data(Archive.get(), rec._data.c_str(), rec._data.size());
}
