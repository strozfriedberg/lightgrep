#include "lg_app.h"
#include "options.h"
#include "lightgrep/api.h"

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
    
    std::stringstream buf;

    writeProgram(opts, buf);

    const std::string s = buf.str();
    const int buf_size = s.size();

    LG_HPROGRAM prog = lg_read_program(s.data(), buf_size);

    REQUIRE(prog);
    REQUIRE(lg_prog_pattern_count(prog) == 3);
    REQUIRE(std::string(lg_prog_pattern_info(prog, 0)->Pattern) == "foo");
    REQUIRE(std::string(lg_prog_pattern_info(prog, 1)->Pattern) == "bar");
    REQUIRE(std::string(lg_prog_pattern_info(prog, 2)->Pattern) == "test");
}
