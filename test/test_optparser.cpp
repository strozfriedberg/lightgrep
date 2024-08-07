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

#include <string>
#include <type_traits>
#include <vector>

#include "boost_program_options.h"

#include "options.h"
#include "optparser.h"

TEST_CASE("kAndpIncompatibleOptions") {
  const char* argv[] = {"lightgrep", "--keywords", "foo", "--pattern", "bar"};
  Options opts;
  po::options_description desc;

  REQUIRE_THROWS_AS(
    parse_opts(std::extent_v<decltype(argv)>, argv, desc, opts),
    po::error
  );
}

TEST_CASE("kOptionNoPosArg") {
  const char* argv[] = {"lightgrep", "--keywords", "foo"};
  Options opts;
  po::options_description desc;
  parse_opts(std::extent_v<decltype(argv)>, argv, desc, opts);

  const std::vector<std::string> kf{"foo"}, inputs{"-"};

  REQUIRE(kf == opts.KeyFiles);
  REQUIRE(inputs == opts.Inputs);
}

TEST_CASE("kOptionOnePosArg") {
  const char* argv[] = {"lightgrep", "--keywords", "foo", "bar"};
  Options opts;
  po::options_description desc;
  parse_opts(std::extent_v<decltype(argv)>, argv, desc, opts);

  const std::vector<std::string> kf{"foo"}, inputs{"bar"};

  REQUIRE(kf == opts.KeyFiles);
  REQUIRE(inputs == opts.Inputs);
}

TEST_CASE("endOnePosArg") {
  const char* argv[] = {"lightgrep", "--", "foo"};
  Options opts;
  po::options_description desc;
  parse_opts(std::extent_v<decltype(argv)>, argv, desc, opts);

  const std::vector<std::string> kf{"foo"}, inputs{"-"};

  REQUIRE(kf == opts.KeyFiles);
  REQUIRE(inputs == opts.Inputs);
}

TEST_CASE("endTwoPosArgs") {
  const char* argv[] = {"lightgrep", "--", "foo", "bar"};
  Options opts;
  po::options_description desc;
  parse_opts(std::extent_v<decltype(argv)>, argv, desc, opts);

  const std::vector<std::string> kf{"foo"}, inputs{"bar"};

  REQUIRE(kf == opts.KeyFiles);
  REQUIRE(inputs == opts.Inputs);
}

TEST_CASE("endThreePosArgs") {
  const char* argv[] = {"lightgrep", "--", "foo", "bar", "baz"};
  Options opts;
  po::options_description desc;
  parse_opts(std::extent_v<decltype(argv)>, argv, desc, opts);

  const std::vector<std::string> kf{"foo"}, inputs{"bar", "baz"};

  REQUIRE(kf == opts.KeyFiles);
  REQUIRE(inputs == opts.Inputs);
}

TEST_CASE("programFileOption") {
  const char* argv[] = {"lightgrep", "--program-file", "test-prog.txt", "test1.txt"};
  Options opts;

  po::options_description desc;
  parse_opts(std::extent_v<decltype(argv)>, argv, desc, opts);

  REQUIRE(Options::SEARCH == opts.Command);
  REQUIRE("test-prog.txt" == opts.ProgramFile);
  REQUIRE(0 == opts.KeyFiles.size());
  REQUIRE("test1.txt" == opts.Inputs.at(0));
}

TEST_CASE("programFileAndPatternOption") {
  const char* argv[] = {"lightgrep", "--program-file", "test-prog.txt", "--pattern", "test", "test1.txt"};
  Options opts;

  po::options_description desc;

  REQUIRE_THROWS_AS(
    parse_opts(std::extent_v<decltype(argv)>, argv, desc, opts),
    po::error
  );
}

TEST_CASE("programFileAndKeywordsOption") {
  const char* argv[] = {"lightgrep", "--program-file", "test-prog.txt", "--keywords", "patterns.txt", "test1.txt"};
  Options opts;

  po::options_description desc;

  REQUIRE_THROWS_AS(
    parse_opts(std::extent_v<decltype(argv)>, argv, desc, opts),
    po::error
  );
}

TEST_CASE("memoryMappedOption") {
  const char* argv[] = {"lightgrep", "--program-file", "test-prog.txt", "-C", "3", "test1.txt"};
  Options opts;

  po::options_description desc;
  parse_opts(std::extent_v<decltype(argv)>, argv, desc, opts);

  REQUIRE(Options::SEARCH == opts.Command);
  REQUIRE("test-prog.txt" == opts.ProgramFile);
  REQUIRE(0 == opts.KeyFiles.size());
  REQUIRE(opts.MemoryMapped == true);
}

TEST_CASE("afterAndBeforeContextOption") {
  const char* argv[] = {"lightgrep", "--program-file", "test-prog.txt", "-A", "3", "-B", "5", "test1.txt"};
  Options opts;

  po::options_description desc;
  parse_opts(std::extent_v<decltype(argv)>, argv, desc, opts);

  REQUIRE(Options::SEARCH == opts.Command);
  REQUIRE("test-prog.txt" == opts.ProgramFile);
  REQUIRE(0 == opts.KeyFiles.size());
  REQUIRE(opts.MemoryMapped == true);
  REQUIRE(opts.AfterContext == 3);
  REQUIRE(opts.BeforeContext == 5);
}

TEST_CASE("mmapIncompatibleWithReadFromStdin") {
  const char* argv[] = {"lightgrep", "--program-file", "test-prog.txt", "-A", "3"};
  Options opts;

  po::options_description desc;

  REQUIRE_THROWS_AS(
    parse_opts(std::extent_v<decltype(argv)>, argv, desc, opts),
    po::error
  );
}

TEST_CASE("sampleOptions") {
  const char* argv[] = {"lightgrep", "-c", "sample", "--program-file", "test-prog.txt", "3", "5"};
  Options opts;

  po::options_description desc;
  parse_opts(std::extent_v<decltype(argv)>, argv, desc, opts);

  REQUIRE(Options::SAMPLES == opts.Command);
  REQUIRE("test-prog.txt" == opts.ProgramFile);
  REQUIRE(opts.SampleLimit == 3);
  REQUIRE(opts.LoopLimit == 5);
}

TEST_CASE("readFromStdinWhenNoInputsProvided") {
  const char* argv[] = {"lightgrep", "--program-file", "test-prog.txt"};
  Options opts;

  po::options_description desc;
  parse_opts(std::extent_v<decltype(argv)>, argv, desc, opts);

  REQUIRE(Options::SEARCH == opts.Command);
  REQUIRE("test-prog.txt" == opts.ProgramFile);
  REQUIRE(opts.Inputs.at(0) == "-");
}

TEST_CASE("tooManyPositionalArguments") {
  const char* argv[] = {"lightgrep", "-c", "sample", "--program-file", "test-prog.txt", "3", "5", "this", "is", "too", "many", "positional", "args"};
  Options opts;

  po::options_description desc;

  REQUIRE_THROWS_AS(
    parse_opts(std::extent_v<decltype(argv)>, argv, desc, opts),
    po::too_many_positional_options_error
  );
}

TEST_CASE("withFilenameIncompatibleWithNoFilename") {
  const char* argv[] = {"lightgrep", "-p", "test", "--with-filename", "--no-filename", "test_file.txt"};
  Options opts;

  po::options_description desc;

  REQUIRE_THROWS_AS(
    parse_opts(std::extent_v<decltype(argv)>, argv, desc, opts),
    po::error
  );
}

TEST_CASE("histogramOption") {
  const char* argv[] = {"lightgrep", "-p", "test", "--histogram-file", "histogram.txt", "test_corpora.txt"};
  Options opts;

  boost::program_options::options_description desc;
  parse_opts(std::extent_v<decltype(argv)>, argv, desc, opts);

  REQUIRE(Options::SEARCH == opts.Command);
  REQUIRE(opts.HistogramFile == "histogram.txt");
}

TEST_CASE("Negative context option should align with grep behavior") {
  SECTION("C option should throw exception if negative") {
    const char* argv[] = {"lightgrep", "-p", "test", "-C", "-1", "test_corpora.txt"};
    Options opts;
    boost::program_options::options_description desc;

    CHECK_THROWS_AS(
      parse_opts(std::extent_v<decltype(argv)>, argv, desc, opts),
      boost::program_options::error
    );
  }

  SECTION("A option should throw exception if negative") {
    const char* argv[] = {"lightgrep", "-p", "test", "-A", "-1", "test_corpora.txt"};
    Options opts;
    boost::program_options::options_description desc;

    CHECK_THROWS_AS(
      parse_opts(std::extent_v<decltype(argv)>, argv, desc, opts),
      boost::program_options::error
    );
  }

  SECTION("B option should throw exception if negative") {
    const char* argv[] = {"lightgrep", "-p", "test", "-B", "-1", "test_corpora.txt"};
    Options opts;
    boost::program_options::options_description desc;

    CHECK_THROWS_AS(
      parse_opts(std::extent_v<decltype(argv)>, argv, desc, opts),
      boost::program_options::error
    );
  }


}
