/*
 * Copyright 2024 Aon Cyber Solutions
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
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

  ostream_join_iterator(ostream_type& s, const char_type* c = nullptr) :
    stream(&s), string(c), print_string(nullptr) {}

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
