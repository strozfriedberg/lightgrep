#include <iostream>
#include "hitwriter.h"
#include "stest.h"

#include <sstream>
#include <catch2/catch_test_macros.hpp>

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

TEST_CASE("callbackFn") {
  LG_HITCALLBACK_FN a = &callbackFn<DoNotWritePath, NoContext, true>;
  LG_HITCALLBACK_FN b = &callbackFn<DoNotWritePath, WriteContext, true>;
  LG_HITCALLBACK_FN c = &callbackFn<WritePath, NoContext, true>;
  LG_HITCALLBACK_FN d = &callbackFn<WritePath, WriteContext, true>;
  LG_HITCALLBACK_FN e = &callbackFn<DoNotWritePath, NoContext, false>;

  LG_HITCALLBACK_FN arr[] = {a, b, c, d, e};

  bool shouldWritePath = true;
  bool shouldWriteContext = true;

  LG_HITCALLBACK_FN selection = arr[( 2*shouldWritePath ) + ( shouldWriteContext )];
  REQUIRE(selection == d);

}

TEST_CASE("hitOutputDataAndCallback") {
  STest s("foo");
  std::stringstream stream;
  std::string textToSearch = "this is foo\nthis is bar\nthis is baz\nthis is foobar\nthis is foobaz\nthis is foobarbaz";

  HitOutputData data(stream, s.Prog.get(), '\t', -1, -1);
  data.setPath("path/to/input/file");
  data.setBuffer(textToSearch.data(), textToSearch.size(), 0);

  SECTION("noContextNoPath") {
    LG_SearchHit searchHit{0, 8, 0};
    std::string expected = "0\t8\t0\tfoo\tUS-ASCII\n";
    LG_HITCALLBACK_FN fn = &callbackFn<DoNotWritePath, NoContext, true>;
    fn(&data, &searchHit);
    REQUIRE(expected == stream.str());
  };

  SECTION("noOutput") {
    LG_SearchHit searchHit{0, 8, 0};
    LG_HITCALLBACK_FN fn = &callbackFn<DoNotWritePath, NoContext, false>;
    fn(&data, &searchHit);
    REQUIRE("" == stream.str());
    REQUIRE(1 == data.NumHits);
  };

  SECTION("noContextYesPath") {
    LG_SearchHit searchHit0{0, 8, 0};
    LG_SearchHit searchHit1{44, 47, 0};
    LG_SearchHit searchHit2{59, 62, 0};
    LG_HITCALLBACK_FN fn = &callbackFn<WritePath, NoContext, true>;
    fn(&data, &searchHit0);
    fn(&data, &searchHit1);
    fn(&data, &searchHit2);
    std::string expected = "path/to/input/file\t0\t8\t0\tfoo\tUS-ASCII\npath/to/input/file\t44\t47\t0\tfoo\tUS-ASCII\npath/to/input/file\t59\t62\t0\tfoo\tUS-ASCII\n";
    REQUIRE(expected == stream.str());
    REQUIRE(3 == data.NumHits);
  };

  SECTION("withLineContextNoPath") {
    data.AfterContext = 0;
    data.BeforeContext = 0;

    LG_SearchHit searchHit{0, 8, 0};
    LG_HITCALLBACK_FN fn = &callbackFn<DoNotWritePath, WriteContext, true>;
    fn(&data, &searchHit);
    std::string expected = "0\t8\t0\tfoo\tUS-ASCII\t0\tthis is foo\n";
    REQUIRE(expected == stream.str());
    REQUIRE(1 == data.NumHits);
  };

  SECTION("withLineContextYesPath") {
    data.AfterContext = 0;
    data.BeforeContext = 0;

    LG_SearchHit searchHit{0, 8, 0};
    LG_HITCALLBACK_FN fn = &callbackFn<WritePath, WriteContext, true>;
    fn(&data, &searchHit);
    std::string expected = "path/to/input/file\t0\t8\t0\tfoo\tUS-ASCII\t0\tthis is foo\n";
    REQUIRE(expected == stream.str());
    REQUIRE(1 == data.NumHits);
  };

  SECTION("decodeContextNoLineContext") {
    data.AfterContext = 0;
    data.BeforeContext = 0;
    LG_SearchHit searchHit{8, 11, 0};
    HitBuffer expectedHitBuffer{"this is foo", LG_Window{8, 11}};
    HitBuffer actualHitBuffer = data.decodeContext(searchHit);

    REQUIRE(expectedHitBuffer.context == actualHitBuffer.context);
    REQUIRE(expectedHitBuffer.hitWindow.begin == actualHitBuffer.hitWindow.begin);
    REQUIRE(expectedHitBuffer.hitWindow.end == actualHitBuffer.hitWindow.end);

  }

  SECTION("decodeContextNoLineContextSecondLine") {
    data.AfterContext = 0;
    data.BeforeContext = 0;
    LG_SearchHit searchHit{44, 47, 0};

    HitBuffer expectedHitBuffer{"this is foobar", LG_Window{8, 11}};
    HitBuffer actualHitBuffer = data.decodeContext(searchHit);

    REQUIRE(expectedHitBuffer.context == actualHitBuffer.context);
    REQUIRE(expectedHitBuffer.hitWindow.begin == actualHitBuffer.hitWindow.begin);
    REQUIRE(expectedHitBuffer.hitWindow.end == actualHitBuffer.hitWindow.end);
    REQUIRE(actualHitBuffer.hit() == "foo");
  }
}

TEST_CASE("getHistogramFromHitOutputData") {
  STest s({"c[auo]t", "foo", "[bch]at"});
  std::stringstream stream;
  std::string textToSearch = "this is a cat in a hat\nfoobar\nhere is another cat";

  HitOutputData data(stream, s.Prog.get(), '\t', -1, -1);
  data.setPath("path/to/input/file");
  data.setBuffer(textToSearch.data(), textToSearch.size(), 0);

  // hit: {pattern, userIndex, count}

  std::map<std::tuple<std::string, std::string, int>, int> expected_histogram {
    {{"cat", "c[auo]t", 0}, 2},
    {{"cat", "[bch]at", 2}, 2},
    {{"hat", "[bch]at", 2}, 1},
    {{"foo", "foo", 1}, 1}
  };

  REQUIRE(expected_histogram == data.Histogram);

}
