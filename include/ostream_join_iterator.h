#pragma once

#include <ostream>
#include <iterator>

template<typename T, typename CharT = char,
         typename Traits = std::char_traits<CharT>>
class ostream_join_iterator :
  public std::iterator<std::output_iterator_tag, void, void, void, void>
{
public:
  typedef CharT char_type;
  typedef Traits traits_type;
  typedef std::basic_ostream<CharT,Traits> ostream_type;

  ostream_join_iterator(ostream_type& s, const char_type* c = 0) :
    stream(&s), string(c), print_string(0) {}

  ostream_join_iterator& operator=(const T& val) {
    if (print_string) *stream << print_string;
    print_string = string;
    *stream << val;
    return *this;
  }

  ostream_join_iterator& operator*() { return *this; }
  ostream_join_iterator& operator++() { return *this; }
  ostream_join_iterator& operator++(int) { return *this; }

private:
  ostream_type* stream;
  const char_type* string;
  const char_type* print_string;
};
