/*
  liblightgrep: not the worst forensics regexp engine
  Copyright (C) 2013, Lightbox Technologies, Inc

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

#include "catch.hpp"

#include <utility>

#include "vectorfamily.h"

template <typename V, typename L>
void empty_test(V&& v, L&& l) {
  REQUIRE(0u == v.size(l));
  REQUIRE(0 == v.end(l) - v.begin(l));

  REQUIRE_THROWS(v.at(l, 0));

  REQUIRE(v.end(l) == v.begin(l));
  REQUIRE(v.end(l) == v.find(l, 3));
}

TEST_CASE("vectorfamily_empty_Test") {
  VectorFamily<int> v;
  VectorFamily<int>::List l;
  empty_test(v, l);
}

TEST_CASE("vectorfamily_const_empty_Test") {
  const VectorFamily<int> v;
  const VectorFamily<int>::List l;
  empty_test(v, l);
}

template <typename V, typename L>
void one_test(V&& v, L&& l) {
  REQUIRE(1u == v.size(l));
  REQUIRE(1 == v.end(l) - v.begin(l));

  REQUIRE(3 == v.at(l, 0));
  // REQUIRE_THROWS((v.at(l, 1)));

  REQUIRE(3 == *v.begin(l));
  REQUIRE(3 == *(v.end(l) - 1));

  REQUIRE(v.begin(l) == v.find(l, 3));
  REQUIRE(3 == *v.find(l, 3));

  REQUIRE(v.end(l) == v.find(l, 4));
}

TEST_CASE("vectorfamily_one_Test") {
  VectorFamily<int> v;
  VectorFamily<int>::List l;
  v.add(l, 3);
  one_test(v, l);
}

TEST_CASE("vectorfamily_one_const_Test") {
  VectorFamily<int> v;
  VectorFamily<int>::List l;
  v.add(l, 3);
  one_test(std::as_const(v), std::as_const(l));
}

template <typename V, typename L>
void two_test(V&& v, L&& l) {
  REQUIRE(2u == v.size(l));
  REQUIRE(2 == v.end(l) - v.begin(l));

  REQUIRE(3 == v.at(l, 0));
  REQUIRE(4 == v.at(l, 1));
  // REQUIRE_THROWS_AS(v.at(l, 2), std::runtime_error);

  REQUIRE(3 == *v.begin(l));
  REQUIRE(4 == *(v.begin(l) + 1));

  REQUIRE(3 == *(v.end(l) - 2));
  REQUIRE(4 == *(v.end(l) - 1));

  REQUIRE(v.begin(l) == v.find(l, 3));
  REQUIRE(3 == *v.find(l, 3));

  REQUIRE(v.begin(l) + 1 == v.find(l, 4));
  REQUIRE(4 == *v.find(l, 4));

  REQUIRE(v.end(l) == v.find(l, 5));
}

TEST_CASE("vectorfamily_two_Test") {
  VectorFamily<int> v;
  VectorFamily<int>::List l;
  v.add(l, 3);
  v.add(l, 4);
  two_test(v, l);
}

TEST_CASE("vectorfamily_two_const_Test") {
  VectorFamily<int> v;
  VectorFamily<int>::List l;
  v.add(l, 3);
  v.add(l, 4);
  two_test(std::as_const(v), std::as_const(l));
}

template <typename V, typename L>
void three_test(V&& v, L&& l) {
  REQUIRE(3u == v.size(l));
  REQUIRE(3 == v.end(l) - v.begin(l));

  REQUIRE(3 == v.at(l, 0));
  REQUIRE(4 == v.at(l, 1));
  REQUIRE(5 == v.at(l, 2));
  // REQUIRE_THROWS_AS(v.at(l, 3), std::runtime_error);

  REQUIRE(3 == *v.begin(l));
  REQUIRE(4 == *(v.begin(l) + 1));
  REQUIRE(5 == *(v.begin(l) + 2));

  REQUIRE(3 == *(v.end(l) - 3));
  REQUIRE(4 == *(v.end(l) - 2));
  REQUIRE(5 == *(v.end(l) - 1));

  REQUIRE(v.begin(l) == v.find(l, 3));
  REQUIRE(3 == *v.find(l, 3));

  REQUIRE(v.begin(l) + 1 == v.find(l, 4));
  REQUIRE(4 == *v.find(l, 4));

  REQUIRE(v.begin(l) + 2 == v.find(l, 5));
  REQUIRE(5 == *v.find(l, 5));
}

TEST_CASE("vectorfamily_three_Test") {
  VectorFamily<int> v;
  VectorFamily<int>::List l;
  v.add(l, 3);
  v.add(l, 4);
  v.add(l, 5);
  three_test(v, l);
}

TEST_CASE("vectorfamily_three_const_Test") {
  VectorFamily<int> v;
  VectorFamily<int>::List l;
  v.add(l, 3);
  v.add(l, 4);
  v.add(l, 5);
  three_test(std::as_const(v), std::as_const(l));
}

TEST_CASE("vectorfamily_empty_remove_Test") {
  VectorFamily<int> v;
  VectorFamily<int>::List l;
  REQUIRE_THROWS_AS(v.remove(l, 42), std::runtime_error);
}

TEST_CASE("vectorfamily_one_remove_Test") {
  VectorFamily<int> v;
  VectorFamily<int>::List l;
  v.add(l, 42);
  REQUIRE(1u == v.size(l));
  REQUIRE_THROWS_AS(v.remove(l, 1), std::runtime_error);
  REQUIRE(1u == v.size(l));
  v.remove(l, 42);
  REQUIRE(0u == v.size(l));
}

TEST_CASE("vectorfamily_two_remove_first_Test") {
  VectorFamily<int> v;
  VectorFamily<int>::List l;
  v.add(l, 42);
  v.add(l, 43);
  REQUIRE(2u == v.size(l));
  REQUIRE_THROWS_AS(v.remove(l, 1), std::runtime_error);
  REQUIRE(2u == v.size(l));
  v.remove(l, 42);
  REQUIRE(1u == v.size(l));
  REQUIRE(43 == v.at(l, 0));
}

TEST_CASE("vectorfamily_two_remove_second_Test") {
  VectorFamily<int> v;
  VectorFamily<int>::List l;
  v.add(l, 42);
  v.add(l, 43);
  REQUIRE(2u == v.size(l));
  REQUIRE_THROWS_AS(v.remove(l, 1), std::runtime_error);
  REQUIRE(2u == v.size(l));
  v.remove(l, 43);
  REQUIRE(1u == v.size(l));
  REQUIRE(42 == v.at(l, 0));
}

TEST_CASE("vectorfamily_three_remove_Test") {
  VectorFamily<int> v;
  VectorFamily<int>::List l;
  v.add(l, 42);
  v.add(l, 43);
  v.add(l, 44);
  REQUIRE(3u == v.size(l));
  REQUIRE_THROWS_AS(v.remove(l, 1), std::runtime_error);
  REQUIRE(3u == v.size(l));
  v.remove(l, 43);
  REQUIRE(2u == v.size(l));
  REQUIRE(42 == v.at(l, 0));
  REQUIRE(44 == v.at(l, 1));
}

TEST_CASE("vectorfamily_empty_clear_Test") {
  VectorFamily<int> v;
  VectorFamily<int>::List l;
  REQUIRE(0u == v.size(l));
  v.clear(l);
  REQUIRE(0u == v.size(l));
}

TEST_CASE("vectorfamily_one_clear_Test") {
  VectorFamily<int> v;
  VectorFamily<int>::List l;
  v.add(l, 4);
  REQUIRE(1u == v.size(l));
  v.clear(l);
  REQUIRE(0u == v.size(l));
}

TEST_CASE("vectorfamily_two_clear_Test") {
  VectorFamily<int> v;
  VectorFamily<int>::List l;
  v.add(l, 4);
  v.add(l, 5);
  REQUIRE(2u == v.size(l));
  v.clear(l);
  REQUIRE(0u == v.size(l));
}

TEST_CASE("vectorfamily_three_clear_Test") {
  VectorFamily<int> v;
  VectorFamily<int>::List l;
  v.add(l, 4);
  v.add(l, 5);
  v.add(l, 6);
  REQUIRE(3u == v.size(l));
  v.clear(l);
  REQUIRE(0u == v.size(l));
}

TEST_CASE("vectorfamily_one_clear_one_keep_Test") {
  VectorFamily<int> v;
  VectorFamily<int>::List l1, l2;
  v.add(l1, 4);
  v.add(l2, 5);
  REQUIRE(1u == v.size(l1));
  REQUIRE(1u == v.size(l2));
  v.clear(l1);
  REQUIRE(0u == v.size(l1));
  REQUIRE(1u == v.size(l2));
  REQUIRE(5 == v.at(l2, 0));
}

TEST_CASE("vectorfamily_insert_front_Test") {
  VectorFamily<int> v;
  VectorFamily<int>::List l;

  REQUIRE(0u == v.size(l));
  v.insert(l, 0, 17);
  REQUIRE(1u == v.size(l));
  REQUIRE(17 == v.at(l, 0));
  v.insert(l, 0, 18);
  REQUIRE(2u == v.size(l));
  REQUIRE(18 == v.at(l, 0));
  REQUIRE(17 == v.at(l, 1));
}

TEST_CASE("vectorfamily_insert_back_Test") {
  VectorFamily<int> v;
  VectorFamily<int>::List l;

  REQUIRE(0u == v.size(l));
  v.insert(l, 0, 17);
  REQUIRE(1u == v.size(l));
  REQUIRE(17 == v.at(l, 0));
  v.insert(l, 1, 18);
  REQUIRE(2u == v.size(l));
  REQUIRE(17 == v.at(l, 0));
  REQUIRE(18 == v.at(l, 1));
}

TEST_CASE("vectorfamily_insert_mid_Test") {
  VectorFamily<int> v;
  VectorFamily<int>::List l;

  REQUIRE(0u == v.size(l));
  v.insert(l, 0, 17);
  REQUIRE(1u == v.size(l));
  REQUIRE(17 == v.at(l, 0));
  v.insert(l, 1, 18);
  REQUIRE(2u == v.size(l));
  REQUIRE(17 == v.at(l, 0));
  REQUIRE(18 == v.at(l, 1));
  v.insert(l, 1, 19);
  REQUIRE(3u == v.size(l));
  REQUIRE(17 == v.at(l, 0));
  REQUIRE(19 == v.at(l, 1));
  REQUIRE(18 == v.at(l, 2));
}
