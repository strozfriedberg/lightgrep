#pragma once

#include <fstream>
#include <iostream>
#include <iterator>
#include <memory>
#include <string>
#include <utility>

#include <tsk/libtsk.h>

class BlockSequence {
public:
  virtual ~BlockSequence() {}

  class Iterator {
  public:
    using value_type = std::pair<const uint8_t*, const uint8_t*>;
    using pointer = const value_type*;
    using reference = const value_type&;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::input_iterator_tag;

    Iterator(): seq(nullptr), cur(nullptr, nullptr) {
    }

    Iterator(BlockSequence* seq): seq(seq), cur(nullptr, nullptr) {
      ++*this;
    }

    Iterator(const Iterator&) = default;

    Iterator(Iterator&&) = default;

    Iterator& operator=(const Iterator&) = default;

    Iterator& operator=(Iterator&&) = default;

    reference operator*() const {
      return cur;
    }

    pointer operator->() const {
      return &cur;
    }

    Iterator& operator++() {
      if (seq->advance()) {
        cur = seq->cur();
      }
      else {
        seq = nullptr;
      }
      return *this;
    }

    Iterator operator++(int) {
      Iterator i(*this);
      ++*this;
      return i;
    }

    bool operator==(const Iterator& r) const {
      return seq ? r.seq && seq->offset() == r.seq->offset() : !r.seq;
    }

    bool operator!=(const Iterator& r) const { return !(r == *this); }

  private:
    BlockSequence* seq;
    value_type cur;
  };

  virtual Iterator begin() {
    return Iterator(this);
  }

  virtual Iterator end() const {
    return Iterator();
  }

protected:
  virtual bool advance() = 0;

  virtual std::pair<const uint8_t*, const uint8_t*> cur() const = 0;

  virtual size_t offset() const = 0;
};

class EmptyBlockSequence: public BlockSequence {
public:
  virtual ~EmptyBlockSequence() {}

  virtual Iterator begin() override {
    return end();
  }

protected:
  virtual bool advance() {
    return false;
  }

  virtual std::pair<const uint8_t*, const uint8_t*> cur() const {
    return std::make_pair(nullptr, nullptr);
  }

  virtual size_t offset() const {
    return 0;
  }
};

/*
class SingleBufferBlockSequence: public BlockSequence {
public:
  SingleBufferBlockSequence(const uint8_t* beg, const uint8_t* end):
    beg(beg), pos(nullptr), end(end) {}

  virtual ~SingleBufferBlockSequence() {}

protected:
  virtual bool advance() {
    pos = pos ? end : beg;
    return pos != end;
  }

  virtual std::pair<const uint8_t*, const uint8_t*> cur() const {
    return std::make_pair(pos, end);
  }

  virtual size_t offset() const {
    return pos - beg;
  }

private:
  const uint8_t* beg;
  const uint8_t* pos;
  const uint8_t* end;
};
*/

class FileBlockSequence: public BlockSequence {
public:
  FileBlockSequence(const std::string& path):
    path(path),
    off(0),
    rlen(0),
    size(0),
    bufend(&buf[0])
  {
  }

  virtual ~FileBlockSequence() {}

  virtual Iterator begin() override {
    in.open(path, std::ios::binary);
    return in ? Iterator(this) : end();
  }

protected:
  virtual bool advance() override {
    off += rlen;

    const bool ok = bool(in);

    in.read(reinterpret_cast<char*>(buf), sizeof(buf));
    rlen = in.gcount();
    bufend = buf + rlen;

    return ok;
  }

  virtual std::pair<const uint8_t*, const uint8_t*> cur() const {
    return std::make_pair(&buf[0], bufend);
  }

  virtual size_t offset() const {
    return off;
  }

private:
  std::string path;
  std::ifstream in;

  size_t off;
  ssize_t rlen;
  size_t size;
  uint8_t buf[8192];
  uint8_t* bufend;
};

class TskBlockSequence: public BlockSequence {
public:
  TskBlockSequence(std::unique_ptr<TSK_FS_FILE, void(*)(TSK_FS_FILE*)> f):
    file(std::move(f)),
    off(0),
    rlen(0)
  {
    // TODO: could this return null?
    const TSK_FS_ATTR* attr = tsk_fs_file_attr_get(file.get());
    size = attr ? attr->size : 0;
  }

  virtual ~TskBlockSequence() {}

protected:
  virtual bool advance() override {
    // TODO: check that size and final offset comport

    // advance offset by the previous read length
    off += rlen;

    if (off >= size) {
      bufend = &buf[0];
      return false;
    }

    // fill the buffer
    rlen = tsk_fs_file_read(
      file.get(), off,
      reinterpret_cast<char*>(buf), sizeof(buf),
      TSK_FS_FILE_READ_FLAG_NONE
    );

    // mark the end of the data read
    if (rlen < 0) {
      std::cerr << "Error: " << tsk_error_get() << std::endl;
      bufend = &buf[0];
    }
    else {
      bufend = buf + rlen;
    }

    return bufend > &buf[0];
  }

  virtual std::pair<const uint8_t*, const uint8_t*> cur() const {
    return std::make_pair(&buf[0], bufend);
  }

  // the offset of the data at cur().first
  virtual size_t offset() const {
    return off;
  }

private:
  std::unique_ptr<TSK_FS_FILE, void(*)(TSK_FS_FILE*)> file;
  size_t off;
  ssize_t rlen;
  size_t size;
  uint8_t buf[8192];
  uint8_t* bufend;
};
