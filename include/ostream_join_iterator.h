/*
  liblightgrep: not the worst forensics regexp engine
  Copyright (C) 2012 Lightbox Technologies, Inc

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

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
