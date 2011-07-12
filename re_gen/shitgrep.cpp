#include <pcre.h>

#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <cerrno>
#include <cstring>
#include <fstream>
#include <istream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <stdexcept>

#include <boost/function.hpp>

class Regex {

public:
  Regex(const char* pattern) {
    // Compile the pattern
    const char* error_str;
    int error_off;

    re = pcre_compile(
      pattern,
      PCRE_DOTALL | PCRE_NO_AUTO_CAPTURE,
      &error_str,
      &error_off,
      NULL
    );

    if (re == NULL) {
      std::ostringstream ss;
      ss << "regex compilation failed at offset " << error_off
         << ": " << error_str;

      throw std::runtime_error(ss.str());
    }

    // Study the pattern
    extra = pcre_study(re, 0, &error_str);
    if (error_str != NULL) {
      std::ostringstream ss;
      ss << "regex study failed: " << error_str;

      throw std::runtime_error(ss.str());
    }
  }
    
  ~Regex() {
    free(re);
    free(extra);
  }

  pcre* re;
  pcre_extra *extra;
};

int do_one_match(
  const Regex& re,
  const char* text, const size_t text_len, const unsigned int offset,
  int* ovector, const unsigned int ovector_size)
{
  int matches = pcre_exec( 
    re.re,
    re.extra,
    text,
    text_len,
    offset,
    0,
    ovector,
    ovector_size
  );

  if (matches == PCRE_ERROR_NOMATCH) return 0;

  if (matches == 0) {
    // this should never happen, because PCRE_NO_AUTO_CAPTURE
    // is set for the pattern
    throw std::runtime_error("ovector is too small!");
  }
    
  if (matches < 0) {
    std::ostringstream ss;
    ss << "pcre_exec: " << matches;
    throw std::runtime_error(ss.str());
  }

  return matches;
}

unsigned int match(
  const char* pattern, unsigned int patnum,
  const char* text, size_t text_len, const char* charset,
  boost::function<void (int,int,unsigned int,const char*,const char*)> callback)
{
  const Regex re(pattern);

  const unsigned int ovector_size = 3;
  int ovector[ovector_size];

  unsigned int offset = 0;
  unsigned int total = 0;

  int matches;

  // check for a match on the empty string
  const char* empty = "";
  if (do_one_match(re, empty, 0, 0, ovector, ovector_size) > 0) {
    // lightgrep rejects patterns which match the empty string, so
    // reject this patern with the same error message as lightgrep
    std::cerr << "state 0 is not allowed as a final state of the NFA"
              << std::endl;
    return 0; 
  }

  do {
    matches = do_one_match(re, text, text_len, offset, ovector, ovector_size);

    if (matches == 0) return total;

    // run the callback for this match
    callback(ovector[0], ovector[1]-ovector[0], patnum, pattern, charset);

    total += matches;

    // advance to match end, but at least one char
    offset = std::max(ovector[0]+1, ovector[1]);

  } while (offset < text_len); 

  return total;
}

void match_printer(int mpos, int mlen, unsigned int patnum,
                   const char* pattern, const char* charset) {
  std::cout << mpos << '\t'
            << mlen << '\t'
            << patnum << '\t'
            << pattern << '\t'
            << charset << '\n';  
}

const char* help_short() {
  return
    "Usage: shitgrep PATTERN_FILE FILE\n"
    "Try `shitgrep --help' for more information.";
}

const char* help_long() {
  return
    "Usage: shitgrep PATTERN_FILE FILE\n"
    "Search for each pattern from PATTERN_FILE in FILE.\n"
    "\n"
    "Patterns are given one per line in PATTERN_FILE.\n"
    "\n"
    "shitgrep is a state-of-the-art search tool which supports single-\n"
    "threaded, non-distributed searching, and offers search times which\n"
    "rival looking for matches by hand.\n"
    "\n"
    "Allowed options:\n"
    "  --help\t\tprint this help message\n"
    "  -p arg\t\tspecify a single keyword instead of a pattern file\n"
    "\n";
}

void do_matches(std::istream& is, const char* text, size_t text_len) {
  using namespace std;

  //
  // Iterate over the pattern file
  //
  unsigned int matches = 0;
  unsigned int patnum = 0;

  string pattern;

  while (!is.eof()) {
    getline(is, pattern);
    if (pattern.empty()) continue; // skip empty lines 

    cerr << patnum << endl;

    //
    // Match, shitgrep! Match!
    //
    matches += match(
      pattern.c_str(),
      patnum++,
      text,
      text_len,
      "ASCII",
      match_printer
    );
  }

  cerr << matches << " matches" << endl;
}

void* mmap_input(const char* filename, int& fd, size_t& text_len) {
  using namespace std;

  fd = open(filename, O_RDWR);
  if (fd == -1) {
    stringstream ss;
    ss << "open: " << strerror(errno) << endl;
    throw runtime_error(ss.str());
  }

  // get the file size
  struct stat st;
  if (fstat(fd, &st) == -1) {
    stringstream ss;
    ss << "stat: " << strerror(errno) << endl;
    throw runtime_error(ss.str());
  }

  text_len = st.st_size;

  // We extend the text by one byte so it can be null-terminated.
  // Note that you can't extend the file while it's mmapped, so
  // we have to do this beforehand.
  if (ftruncate(fd, text_len+1) == -1) {
    stringstream ss;
    ss << "ftruncate: " << strerror(errno) << endl;
    throw runtime_error(ss.str());
  }

  void* addr = mmap(NULL, text_len+1, PROT_READ, MAP_PRIVATE, fd, 0);
  if (addr == MAP_FAILED) {
    stringstream ss;
    ss << "mmap: " << strerror(errno) << endl;
    throw runtime_error(ss.str());
  }

  return addr;
}

void unmmap_input(int fd, void* addr, size_t text_len) {
  using namespace std;

  // unmap the file
  if (munmap(addr, text_len+1) == -1) {
    stringstream ss;
    ss << "munmap: " << strerror(errno) << endl;
    throw runtime_error(ss.str());
  }

  // chop off the null terminator we added
  if (ftruncate(fd, text_len) == -1) {
    stringstream ss;
    ss << "ftruncate: " << strerror(errno) << endl;
    throw runtime_error(ss.str());
  }

  // close the file
  if (close(fd) == -1) {
    stringstream ss;
    ss << "close: " << strerror(errno) << endl;
    throw runtime_error(ss.str());
  }
}


int main(int argc, char** argv)
{
  using namespace std;

  //
  // Parse the arguments
  //

  if (argc < 2) {
    cerr << "too few arguments!\n"
         << help_short() << endl;
    return 1;
  }

  if (!strcmp(argv[1], "-h")) {
    // -h prints the short help
    cerr << help_short() << endl;
    return 0;
  }
  else if (!strcmp(argv[1], "--help")) {
    // --help prints the long help
    cerr << help_long() << endl;
    return 0;
  }

  unsigned int text_arg = 0;
  const char* pat;
  bool use_pfile;

  if (!strcmp(argv[1], "-p")) {
    // get pattern from command line
    use_pfile = false;

    if (argc < 3) {
      cerr << "too few arguments!\n"
           << help_short() << endl;
      return 1;
    }

    pat = argv[2];
    text_arg = 3;
  }
  else {
    // get patterns from pattern file  
    use_pfile = true;
    pat = argv[1];
    text_arg = 2;
  }

  if (text_arg + 1 < (unsigned int) argc) {
    cerr << "too many arguments!\n"
         << help_short() << endl;
    return 1;
  }

  const char* text_filename;

  if (text_arg < (unsigned int) argc) {
    // read text from file
    text_filename = argv[text_arg];
  }
  else {
    // read text from stdin
    text_filename = 0;
  }

  //
  // Set up the text
  //
  const char* text;
  size_t text_len;
  int fd;
  void* addr;
  string text_str;

  if (text_filename) {
    // memory-map the text file
    addr = mmap_input(text_filename, fd, text_len);
    text = static_cast<char*>(addr);
  }
  else {
    // read the whole text file from stdin
    text_str.assign(istreambuf_iterator<char>(cin),
                    istreambuf_iterator<char>());
    text = text_str.data();
    text_len = text_str.length();
  }

  //
  // Iterate over the pattern file
  //
  if (use_pfile) {
    ifstream ifs(pat, ios::in | ios::binary);
  
    if (!ifs.is_open()) {
      cerr << "failed to open " << argv[1] << ": " << strerror(errno) << endl;
      return errno;
    }

    do_matches(ifs, text, text_len);
  }
  else {
    stringstream ss(pat, ios::in | ios::binary);
    do_matches(ss, text, text_len);
  }

  //
  // Cleanup
  //
  if (text_filename) {
    unmmap_input(fd, addr, text_len);
  }
}
