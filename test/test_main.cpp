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

#include "lg_app.h"
#include "options.h"
#include "lightgrep/api.h"

#include <memory>
#include <sstream>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("testWriteProgramWithBinaryOpt") {
    Options opts;
    opts.CmdLinePatterns = {"foo", "bar", "test"};
    opts.Encodings = {"ASCII"};
    opts.LiteralMode = true;
    opts.CaseInsensitive = false;
    opts.UnicodeMode = false;
    opts.DeterminizeDepth = 10;
    opts.Binary = true;
    
    std::ostringstream buf;

    writeProgram(opts, buf);

    const std::string s = buf.str();
    const int buf_size = s.size();

    std::unique_ptr<ProgramHandle,void(*)(ProgramHandle*)> prog(
      lg_read_program(s.data(), buf_size),
      lg_destroy_program
    );

    REQUIRE(prog);
    REQUIRE(lg_prog_pattern_count(prog.get()) == 3);
    REQUIRE(std::string(lg_prog_pattern_info(prog.get(), 0)->Pattern) == "foo");
    REQUIRE(std::string(lg_prog_pattern_info(prog.get(), 1)->Pattern) == "bar");
    REQUIRE(std::string(lg_prog_pattern_info(prog.get(), 2)->Pattern) == "test");
}
