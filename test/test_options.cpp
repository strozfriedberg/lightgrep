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

#include <catch2/catch_test_macros.hpp>

#include "config.h"

#include <vector>

#include "options.h"

TEST_CASE("getKeyFilesFromActualFiles") {
  Options opts;
  opts.KeyFiles = {
    LG_TEST_DATA_DIR "/pats.0",
    LG_TEST_DATA_DIR "/pats.1",
    LG_TEST_DATA_DIR "/pats.2"
  };

  const std::vector<std::pair<std::string,std::string>> expected = {
    { opts.KeyFiles[0], "a*b+\tUTF-8,UTF-16LE\t0\t0\nJoel\tUTF-8\t1\t1\n" },
    { opts.KeyFiles[1], "(All work and no play makes Jack a dull boy\\. )+\nBALLS BALLS BALLS BALLS BALLS BALLS BALLS BALLS BALLS BALLS BALLS BALLS BALLS BALLS BALLS BALLS BALLS BALLS BALLS BALLS BALLS BALLS BALLS BALLS BALLS BALLS BALLS BALLS BALLS BALLS BALLS BALLS\n" },
    { opts.KeyFiles[2], "\n\n\n\n\n\n\n\n\n" }
  };

  REQUIRE(expected == opts.getPatternLines());
}
