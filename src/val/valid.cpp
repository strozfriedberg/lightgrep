#include <cstring>
#include <iostream>
#include <memory>
#include <set>
#include <string>
#include <vector>

#include <unicode/ucnv.h>

#include "ascii.h"
#include "basic.h"
#include "encoder.h"
#include "icuencoder.h"
#include "utf8.h"
#include "utf16.h"
#include "utf32.h"

void write_tests(Encoder& utf8, byte* buf_utf8, Encoder& enc, byte* buf_enc) {
  UnicodeSet valid(enc.validCodePoints());

  std::cerr << enc.name() << ": " << valid << std::endl;

  for (UnicodeSet::range r : valid) {
    for ( ; r.first < r.second; ++r.first) {
      // write pattern count
      const uint32 pat_count = 1;
      std::cout.write(reinterpret_cast<const char*>(&pat_count), sizeof(pat_count));

      // write pattern
      uint32 len_utf8 = utf8.write(r.first, buf_utf8);

      switch (r.first) {
      // escape metacharacters
      case 0:
        ++len_utf8;
        std::cout.write(reinterpret_cast<const char*>(&len_utf8), sizeof(len_utf8));
        --len_utf8;
        std::cout << "\\0";
        break;
      case '.':
      case '*':
      case '+':
      case '?':
      case '\\':
      case '[':
      case '|':
      case '(':
      case ')':
      case '^':
        ++len_utf8;
        std::cout.write(reinterpret_cast<const char*>(&len_utf8), sizeof(len_utf8));
        --len_utf8;
        std::cout << '\\';
        std::cout.write(reinterpret_cast<char*>(buf_utf8), len_utf8);
        break;
      // let everytyhing else through as-is
      default:
        std::cout.write(reinterpret_cast<const char*>(&len_utf8), sizeof(len_utf8));
        std::cout.write(reinterpret_cast<char*>(buf_utf8), len_utf8);
        break;
      }

      // write options
      std::cout.put(0);
      std::cout.put(0);

      // write encoding name
      const uint32 len_name = enc.name().length();
      std::cout.write(reinterpret_cast<const char*>(&len_name), sizeof(len_name));
      std::cout << enc.name();
       
      // write text
      const uint32 len_enc = enc.write(r.first, buf_enc);

if (len_enc == 0) {
  std::cerr << enc.name() << ' ' << std::hex << r.first << std::endl;
}

      std::cout.write(reinterpret_cast<const char*>(&len_enc), sizeof(len_enc));
      std::cout.write(reinterpret_cast<char*>(buf_enc), len_enc);

      // write match count
      const uint32 match_count = 1;
      std::cout.write(reinterpret_cast<const char*>(&match_count), sizeof(match_count));

      // write matches
      const uint64 match_beg = 0, match_end = len_enc, pat_num = 0;
      std::cout.write(reinterpret_cast<const char*>(&match_beg), sizeof(match_beg));
      std::cout.write(reinterpret_cast<const char*>(&match_end), sizeof(match_end));
      std::cout.write(reinterpret_cast<const char*>(&pat_num), sizeof(pat_num));
    }
  }
}

std::shared_ptr<Encoder> getEncoder(const std::string& name) {
  if (name == "ASCII") {
    return std::make_shared<ASCII>();
  }
  else if (name == "UTF-8") {
    return std::make_shared<UTF8>();
  }
  else if (name == "UTF-16LE") {
    return std::make_shared<UTF16LE>();
  }
  else if (name == "UTF-16BE") {
    return std::make_shared<UTF16BE>();
  }
  else if (name == "UTF-32LE") {
    return std::make_shared<UTF32LE>();
  }
  else if (name == "UTF-32BE") {
    return std::make_shared<UTF32BE>();
  }
  else {
    return std::make_shared<ICUEncoder>(name);
  }
}

int main(int argc, char** argv) {
  UTF8 utf8;
  std::unique_ptr<byte[]> buf_utf8(new byte[utf8.maxByteLength()]);

  std::vector<std::string> encodings;

  if (argc > 1) {
    // produce tests for the requested encodings
    encodings.assign(argv + 1, argv + argc);
  }
  else {
    // produce tests for all encodings

    //
    // Encodings provided by Lightgrep
    //
    encodings.insert(encodings.end(), {
      "ASCII",
      "UTF-8",
      "UTF-16LE",
      "UTF-16BE",
      "UTF-32LE",
      "UTF-32BE"
    });

    //
    // Encodings provided by ICU
    //

    // Encodings to skip with ICU
    const std::set<std::string> skip{
      // we provide these, use ours
      "ASCII",
      "UTF-8",
      "UTF-16LE",
      "UTF-16BE",
      "UTF-32LE",
      "UTF-32BE",

      // skip these due to BOMs
      "UTF-16",
      "UTF-16,version=1",
      "UTF-16,version=2",
      "UTF-16LE,version=1",
      "UTF-16BE,version=1",
      "UTF-32",

      // skip these because they're confusing
      "UTF16_OppositeEndian",
      "UTF16_PlatformEndian",
      "UTF32_OppositeEndian",
      "UTF32_PlatformEndian",

      // stateful
      "BOCU-1",               // IBM MIME-friendly Unicode encoding
      "IMAP-mailbox-name",    // modified UTF-7
      "ISCII,version=0",      // Indian Script Code for Information Interchange
      "ISCII,version=1",
      "ISCII,version=2",
      "ISCII,version=3",
      "ISCII,version=4",
      "ISCII,version=5",
      "ISCII,version=6",
      "ISCII,version=7",
      "ISCII,version=8",
      "ISO_2022,locale=ko,version=0", // also not 1-1
      "ISO_2022,locale=zh,version=2", // also not 1-1
      "LMBCS-1",  // Louts Multi-Byte Character Set
                  // http://web.archive.org/web/20050516054001/http://www.batutis.com/i18n/papers/lmbcs/LMBCS.html
      "SCSU",                 // Symbian, SQL Server 2008, Reuters
      "UTF-7",                // crazy
      "ibm-1390_P110-2003",   // Japanese EBCDIC, extends IBM 930
      "ibm-1399_P110-2003",   // Japanese EBCDIC, extends IBM 939
      "ibm-16684_P110-2003",  // Japanese EBCDIC, extends IBM 300
      "x11-compound-text",    // http://www.x.org/docs/CTEXT/ctext.pdf
    };

    const int32 clen = ucnv_countAvailable();
    for (int32 i = 0; i < clen; ++i) {
      const char* name = ucnv_getAvailableName(i);

      // skip encodings we want to omit
      if (skip.find(name) == skip.end()) {
        encodings.push_back(name);
      }
    }
  }

  // generate test data for each requested encoding
  for (const std::string& ename : encodings) {
    std::shared_ptr<Encoder> enc(getEncoder(ename));
    std::unique_ptr<byte[]> buf_enc(new byte[enc->maxByteLength()+20]);
    write_tests(utf8, buf_utf8.get(), *enc.get(), buf_enc.get());
  } 

  return 0;
}
