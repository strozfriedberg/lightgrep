#include <iostream>
#include <sstream>

#include <catch2/catch_test_macros.hpp>

#include "hitwriter.h"
#include "stest.h"

/*
TEST_CASE("hitWriterOutput") {
  std::vector<std::pair<uint32_t, uint32_t >> tbl;
  std::vector<std::string> keys,
                             encodings;
  std::stringstream stream;

  keys.push_back("whatever");
  encodings.push_back("ASCII");
  encodings.push_back("UCS-16");

  tbl.push_back(std::make_pair<uint32_t,uint32_t>(0, 0));
  tbl.push_back(std::make_pair<uint32_t,uint32_t>(0, 1));

  HitWriter writer(stream, tbl, keys, encodings);
  writer.collect(SearchHit(0, 10, 0));

  uint64_t offset, end, keyIndex;
  std::string key, encoding;

  stream >> offset >> end >> keyIndex >> key >> encoding;
  REQUIRE(0u == offset);
  REQUIRE(10u == end);
  REQUIRE(0u == keyIndex);
  REQUIRE(std::string("whatever") == key);
  REQUIRE(std::string("ASCII") == encoding);

  writer.collect(SearchHit(2, 22, 1));

  stream >> offset >> end >> keyIndex >> key >> encoding;
  REQUIRE(2u == offset);
  REQUIRE(22u == end);
  REQUIRE(0u == keyIndex);
  REQUIRE(std::string("whatever") == key);
  REQUIRE(std::string("UCS-16") == encoding);
}
*/

const char TXT[] = "0\n1\n2\n3\n4\n5\n6\n7\n8\n9";

TEST_CASE("findLeadingContext0") {
  REQUIRE(TXT+10 == find_leading_context(TXT, TXT+10, 0));
}

TEST_CASE("findLeadingContext1") {
  REQUIRE(TXT+8 == find_leading_context(TXT, TXT+10, 1));
}

TEST_CASE("findLeadingContext2") {
  REQUIRE(TXT+6 == find_leading_context(TXT, TXT+10, 2));
}

TEST_CASE("findLeadingContext3") {
  REQUIRE(TXT+4 == find_leading_context(TXT, TXT+10, 3));
}

TEST_CASE("findLeadingContext4") {
  REQUIRE(TXT+2 == find_leading_context(TXT, TXT+10, 4));
}

TEST_CASE("findLeadingContext5") {
  REQUIRE(TXT == find_leading_context(TXT, TXT+10, 5));
}

TEST_CASE("findLeadingContext6") {
  REQUIRE(TXT == find_leading_context(TXT, TXT+10, 6));
}

TEST_CASE("findTrailingContext0") {
  REQUIRE(TXT+11 == find_trailing_context(TXT+11, TXT+19, 0));
}

TEST_CASE("findTrailingContext1") {
  REQUIRE(TXT+13 == find_trailing_context(TXT+11, TXT+19, 1));
}

TEST_CASE("findTrailingContext2") {
  REQUIRE(TXT+15 == find_trailing_context(TXT+11, TXT+19, 2));
}

TEST_CASE("findTrailingContext3") {
  REQUIRE(TXT+17 == find_trailing_context(TXT+11, TXT+19, 3));
}

TEST_CASE("findTrailingContext4") {
  REQUIRE(TXT+19 == find_trailing_context(TXT+11, TXT+19, 4));
}

TEST_CASE("findTrailingContext5") {
  REQUIRE(TXT+19 == find_trailing_context(TXT+11, TXT+19, 5));
}

TEST_CASE("findTrailingContext6") {
  REQUIRE(TXT+19 == find_trailing_context(TXT+11, TXT+19, 6));
}

TEST_CASE("hitOutputDataAndCallback") {
  const STest s("foo");
  std::ostringstream stream;
  const std::string textToSearch = "this is foo\nthis is bar\nthis is baz\nthis is foobar\nthis is foobaz\nthis is foobarbaz";

  HitOutputData data(stream, s.Prog.get(), '\t', "--", -1, -1, false);
  data.setPath("path/to/input/file");
  data.setBuffer(textToSearch.data(), textToSearch.size(), 0);

  SECTION("noContextNoPath") {
    const LG_SearchHit searchHit{8, 11, 0};
    const std::string expected = "8\t11\t0\tfoo\tUS-ASCII\n";
    const LG_HITCALLBACK_FN fn = &callbackFn<DoNotWritePath, NoContext, true>;
    fn(&data, &searchHit);
    REQUIRE(expected == stream.str());
    REQUIRE(data.HistInfo.Histogram.size() == 0);
  };

  SECTION("noOutput") {
    const LG_SearchHit searchHit{0, 8, 0};
    const LG_HITCALLBACK_FN fn = &callbackFn<DoNotWritePath, NoContext, false>;
    fn(&data, &searchHit);
    REQUIRE("" == stream.str());
    REQUIRE(1 == data.NumHits);
    REQUIRE(data.HistInfo.Histogram.size() == 0);
  };

  SECTION("noContextYesPath") {
    const LG_SearchHit searchHit0{0, 8, 0};
    const LG_SearchHit searchHit1{44, 47, 0};
    const LG_SearchHit searchHit2{59, 62, 0};
    const LG_HITCALLBACK_FN fn = &callbackFn<WritePath, NoContext, true>;
    fn(&data, &searchHit0);
    fn(&data, &searchHit1);
    fn(&data, &searchHit2);
    std::string expected = "path/to/input/file\t0\t8\t0\tfoo\tUS-ASCII\npath/to/input/file\t44\t47\t0\tfoo\tUS-ASCII\npath/to/input/file\t59\t62\t0\tfoo\tUS-ASCII\n";
    REQUIRE(expected == stream.str());
    REQUIRE(3 == data.NumHits);
    REQUIRE(data.HistInfo.Histogram.size() == 0);
  };

  SECTION("withLineContextNoPath") {
    data.OutInfo.AfterContext = 0;
    data.OutInfo.BeforeContext = 0;

    const LG_SearchHit searchHit{0, 8, 0};
    const LG_HITCALLBACK_FN fn = &callbackFn<DoNotWritePath, WriteContext, true>;
    fn(&data, &searchHit);
    std::string expected = "0\t8\t0\tfoo\tUS-ASCII\t0\tthis is foo\n";
    REQUIRE(expected == stream.str());
    REQUIRE(1 == data.NumHits);
    REQUIRE(data.HistInfo.Histogram.size() == 0);
  };

  SECTION("withLineContextYesPath") {
    data.OutInfo.AfterContext = 0;
    data.OutInfo.BeforeContext = 0;

    LG_SearchHit searchHit{0, 8, 0};
    LG_HITCALLBACK_FN fn = &callbackFn<WritePath, WriteContext, true>;
    fn(&data, &searchHit);
    std::string expected = "path/to/input/file\t0\t8\t0\tfoo\tUS-ASCII\t0\tthis is foo\n";
    REQUIRE(expected == stream.str());
    REQUIRE(1 == data.NumHits);
    REQUIRE(data.HistInfo.Histogram.size() == 0);
  };

  SECTION("decodeContextNoLineContext") {
    data.OutInfo.AfterContext = 0;
    data.OutInfo.BeforeContext = 0;
    const LG_SearchHit searchHit{8, 11, 0};
    HitBuffer expectedHitBuffer{"this is foo", LG_Window{8, 11}, 0};
    HitBuffer actualHitBuffer = data.decodeContext(searchHit);

    REQUIRE(expectedHitBuffer.DataOffset == actualHitBuffer.DataOffset);
    REQUIRE(expectedHitBuffer.Context == actualHitBuffer.Context);
    REQUIRE(expectedHitBuffer.HitWindow.begin == actualHitBuffer.HitWindow.begin);
    REQUIRE(expectedHitBuffer.HitWindow.end == actualHitBuffer.HitWindow.end);
    REQUIRE(data.HistInfo.Histogram.size() == 0);
  }

  SECTION("decodeContextNoLineContextSecondLine") {
    data.OutInfo.AfterContext = 0;
    data.OutInfo.BeforeContext = 0;
    const LG_SearchHit searchHit{44, 47, 0};

    const HitBuffer expectedHitBuffer{"this is foobar", LG_Window{8, 11}, 36};
    const HitBuffer actualHitBuffer = data.decodeContext(searchHit);

    REQUIRE(expectedHitBuffer.DataOffset == actualHitBuffer.DataOffset);
    REQUIRE(expectedHitBuffer.Context == actualHitBuffer.Context);
    REQUIRE(expectedHitBuffer.HitWindow.begin == actualHitBuffer.HitWindow.begin);
    REQUIRE(expectedHitBuffer.HitWindow.end == actualHitBuffer.HitWindow.end);
    REQUIRE(actualHitBuffer.hit() == "foo");
    REQUIRE(data.HistInfo.Histogram.size() == 0);
  }

  SECTION("NegativeAfterAndBeforeContextOnlyHitText") {
    data.OutInfo.AfterContext = -1;
    data.OutInfo.BeforeContext = -3;
    const LG_SearchHit searchHit{44, 47, 0};
    const HitBuffer expectedHitBuffer{"foo", LG_Window{0, 3}, 44};
    const HitBuffer actualHitBuffer = data.decodeContext(searchHit);
  
    REQUIRE(expectedHitBuffer.DataOffset == actualHitBuffer.DataOffset);
    REQUIRE(expectedHitBuffer.Context == actualHitBuffer.Context);
    REQUIRE(expectedHitBuffer.HitWindow.begin == actualHitBuffer.HitWindow.begin);
    REQUIRE(expectedHitBuffer.HitWindow.end == actualHitBuffer.HitWindow.end);
    REQUIRE(actualHitBuffer.hit() == "foo");
    REQUIRE(data.HistInfo.Histogram.size() == 0);
  }

  SECTION("Multiple lines of context should be separated by group separator") {
    data.OutInfo.AfterContext = 3;
    data.OutInfo.BeforeContext = 2;

    const LG_SearchHit searchHit0{0, 8, 0};
    const LG_SearchHit searchHit1{44, 47, 0};
    const LG_SearchHit searchHit2{59, 62, 0};
    const LG_HITCALLBACK_FN fn = &callbackFn<WritePath, WriteContext, true>;
    fn(&data, &searchHit0);
    fn(&data, &searchHit1);
    fn(&data, &searchHit2);
    std::string expected = "path/to/input/file\t0\t8\t0\tfoo\tUS-ASCII\t0\tthis is foo\\nthis is bar\\nthis is baz\\nthis is foobar\n--\npath/to/input/file\t44\t47\t0\tfoo\tUS-ASCII\t12\tthis is bar\\nthis is baz\\nthis is foobar\\nthis is foobaz\\nthis is foobarbaz\n--\npath/to/input/file\t59\t62\t0\tfoo\tUS-ASCII\t24\tthis is baz\\nthis is foobar\\nthis is foobaz\\nthis is foobarbaz\n";
    REQUIRE(expected == stream.str());
    REQUIRE(3 == data.NumHits);
    REQUIRE(data.HistInfo.Histogram.size() == 0);
  }
}

TEST_CASE("getHistogramFromHitOutputData") {
  const STest s({"c[auo]t", "foo", "[bch]at"});
  std::ostringstream stream;
  const std::string textToSearch = "this is a cat in a hat\nfoobar\nhere is another cat";

  HitOutputData data(stream, s.Prog.get(), '\t', "--", -1, -1, false);
  data.setPath("path/to/input/file");
  data.setBuffer(textToSearch.data(), textToSearch.size(), 0);
  data.OutInfo.AfterContext = 0;
  data.OutInfo.BeforeContext = 0;

  SearchHit searchHit1{10, 13, 0};
  SearchHit searchHit2{10, 13, 2};
  SearchHit searchHit3{19, 22, 2};
  SearchHit searchHit4{23, 26, 1};
  SearchHit searchHit5{46, 49, 0};
  SearchHit searchHit6{46, 49, 2};

  data.writeHitToHistogram(searchHit1);
  data.writeHitToHistogram(searchHit2);
  data.writeHitToHistogram(searchHit3);
  data.writeHitToHistogram(searchHit4);
  data.writeHitToHistogram(searchHit5);
  data.writeHitToHistogram(searchHit6);

  LG_Histogram expectedHistogram;
  expectedHistogram[HistogramKey{"cat", "c[auo]t", 0}] = 2;
  expectedHistogram[HistogramKey{"cat", "[bch]at", 2}] = 2;
  expectedHistogram[HistogramKey{"foo", "foo", 1}] = 1;
  expectedHistogram[HistogramKey{"hat", "[bch]at", 2}] = 1;

  REQUIRE(expectedHistogram == data.HistInfo.Histogram);
}

TEST_CASE("writeHistogram") {
  const STest s({"c[auo]t", "foo", "[bch]at", "t\r\nf"});
  std::ostringstream stream, histStream;
  const std::string textToSearch = "this is a cat in a hat\r\nfoobar\nhere is another cat in a hat";

  HitOutputData data(stream, s.Prog.get(), '\t', "--", -1, -1, false);
  data.setPath("path/to/input/file");
  data.setBuffer(textToSearch.data(), textToSearch.size(), 0);
  data.OutInfo.AfterContext = 0;
  data.OutInfo.BeforeContext = 0;

  SearchHit searchHit1{10, 13, 0};
  SearchHit searchHit2{10, 13, 2};
  SearchHit searchHit3{19, 22, 2};
  SearchHit searchHit4(21, 25, 3);
  SearchHit searchHit5{24, 27, 1};
  SearchHit searchHit6{47, 50, 0};
  SearchHit searchHit7{47, 50, 2};
  SearchHit searchHit8{56, 59, 2};

  data.writeHitToHistogram(searchHit1);
  data.writeHitToHistogram(searchHit2);
  data.writeHitToHistogram(searchHit3);
  data.writeHitToHistogram(searchHit4);
  data.writeHitToHistogram(searchHit5);
  data.writeHitToHistogram(searchHit6);
  data.writeHitToHistogram(searchHit7);
  data.writeHitToHistogram(searchHit8);

  CAPTURE(data.HistInfo.Histogram);

  data.writeHistogram(histStream);
  std::string expectedOutput = "2\tcat\t0\tc[auo]t\n2\tcat\t2\t[bch]at\n2\that\t2\t[bch]at\n1\tfoo\t1\tfoo\n1\tt\\r\\nf\t3\tt\\r\\nf\n";
  REQUIRE(histStream.str() == expectedOutput);
}

TEST_CASE("testHistogramKeyComp") {
  const std::vector<std::tuple<bool, LG_Histogram::value_type, LG_Histogram::value_type>> tests = {
    {false, {HistogramKey{"foo", "", 1}, 1}, {HistogramKey{"foo", "", 1}, 1}},
    {true, {HistogramKey{"afoo", "", 1}, 1}, {HistogramKey{"foo", "", 1}, 1}},
    {true, {HistogramKey{"foo", "", 1}, 1}, {HistogramKey{"foo", "", 2}, 1}},
    {true, {HistogramKey{"afoo", "", 1}, 1}, {HistogramKey{"foo", "", 2}, 1}},
    {true, {HistogramKey{"foo", "", 1}, 2}, {HistogramKey{"foo", "", 1}, 1}},
    {true, {HistogramKey{"foo", "", 1}, 2}, {HistogramKey{"afoo", "", 1}, 1}},
    {true, {HistogramKey{"foo", "", 2}, 2}, {HistogramKey{"foo", "", 1}, 1}},
    {true, {HistogramKey{"foo", "", 2}, 2}, {HistogramKey{"afoo", "", 1}, 1}},
    {true, {HistogramKey{"cat", "", 2}, 2}, {HistogramKey{"hat", "", 2}, 2}},
    {false, {HistogramKey{"afoo", "afoo", 1}, 1}, {HistogramKey{"foo", "", 2}, 2}},
    {false, {HistogramKey{"hat", "", 2}, 2}, {HistogramKey{"cat", "", 2}, 2}}
  };

  int idx = 0;
  for (const auto& [exp, l, r]: tests) {
    CAPTURE(idx); // prints index of misbehaving iteration if test fails
    REQUIRE(exp == histogramKeyComp(l, r));
    ++idx;
  }
}

TEST_CASE("decodeContextNoLineContextSecondLineAndHistogramEnabled") {
  const STest s("foo");
  std::ostringstream stream;
  const std::string textToSearch = "this is foo\nthis is bar\nthis is baz\nthis is foobar\nthis is foobaz\nthis is foobarbaz";

  HitOutputData data(stream, s.Prog.get(), '\t', "--", -1, -3, true);
  data.setPath("path/to/input/file");
  data.setBuffer(textToSearch.data(), textToSearch.size(), 0);

  const LG_SearchHit searchHit{8, 11, 0};
  const std::string expected = "8\t11\t0\tfoo\tUS-ASCII\n";
  const LG_HITCALLBACK_FN fn = &callbackFn<DoNotWritePath, NoContext, true>;
  fn(&data, &searchHit);
  REQUIRE(expected == stream.str());
  CHECK(data.HistInfo.Histogram.size() == 1);
  auto found = data.HistInfo.Histogram.find(HistogramKey{"foo", "foo", 0});
  REQUIRE(found != data.HistInfo.Histogram.end());
  CHECK(found->second == 1);
}

TEST_CASE("testDecodeContextPassedAsFunction") {
  const STest s("foo");
  HistogramInfo hInfo(true);
  const LG_SearchHit hit{8, 11, 0};
  LG_PatternInfo* info = lg_prog_pattern_info(const_cast<ProgramHandle*>(s.Prog.get()), hit.KeywordIndex);

  auto decodeFn = [](const LG_SearchHit& hit) { return HitBuffer{"", {0,0}, hit.KeywordIndex}; };
  hInfo.writeHitToHistogram(hit, info, decodeFn);
  HistogramKey hKey("", "foo", 0);
  HistogramInfo expectedHist{true};
  expectedHist.Histogram[hKey] = 1;
  REQUIRE(hInfo.Histogram == expectedHist.Histogram);
}

TEST_CASE("HistInfo::writeHitToHistogram Should Use DecodedContext Provided By WriteContext If Present") {
  bool called = false;
  const STest s("foo");
  const std::string textToSearch = "this is foo";
  const LG_SearchHit hit{8, 11, 0};
  LG_PatternInfo* info = lg_prog_pattern_info(const_cast<ProgramHandle*>(s.Prog.get()), hit.KeywordIndex);
  std::ostringstream stream;
  HitOutputData data(stream, s.Prog.get(), '\t', "--", -1, -3, true);
  data.setBuffer(textToSearch.data(), textToSearch.size(), 0);
  auto decodeFn = [&called](const LG_SearchHit& hit) { called = true; return HitBuffer{"", {0,0}, hit.KeywordIndex}; };

  SECTION("Should use cached DecodedContext when WriteContext was called before for the same hit") {
    WriteContext wc;
    wc.write(data, hit);
    data.HistInfo.writeHitToHistogram(hit, info, decodeFn);

    REQUIRE(!called);
  };

  SECTION("Should not use cached DecodedContext if LastSearchHit is different from current SearchHit") {
    const WriteContext wc;
    wc.write(data, hit);
    data.HistInfo.LastSearchHit = LG_SearchHit{7, 10, 0};
    data.HistInfo.writeHitToHistogram(hit, info, decodeFn);

    REQUIRE(called);
  };

  SECTION("Should call decodeContext if no cached DecodedContext") {
    data.HistInfo.writeHitToHistogram(hit, info, decodeFn);
    REQUIRE(called);
  };
}

TEST_CASE("zeroTrailingContextShouldWorkWhenHitsEndWithCR") {
  const STest s(R"(\n.\r)");
  const std::string textToSearch = "\r\nt\r\n";

  std::ostringstream stream;
  HitOutputData data(stream, s.Prog.get(), '\t', "--", 0, 0, false);
  data.setPath("path/to/input/file");
  data.setBuffer(textToSearch.data(), textToSearch.size(), 0);

  const LG_SearchHit searchHit{1, 4, 0};

  const HitBuffer actualHitBuffer = data.decodeContext(searchHit);
  REQUIRE(actualHitBuffer.hit() == "\nt\r");
  REQUIRE(actualHitBuffer.Context == "\r\nt\r");
}
