#include "hitwriter.h"

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

struct HitOutputData {
  std::ostream &out;
  std::string path;
  uint64_t numHits;
  ProgramHandle* Prog;
  char separator;

  void writeContext(const LG_SearchHit& searchHit) {
    // writeLineContext from hitwriter.cpp
  }
};

template<typename PathOutputFn, typename ContextFn, bool shouldOutput>
void callbackFn(void* userData, const LG_SearchHit* searchHit) {
  HitOutputData* data = reinterpret_cast<HitOutputData*>(userData);
  if (shouldOutput) {
    PathOutputFn::write(*data);
    // write hit
    ContextFn::write(*data, *searchHit);
  }

  data->numHits++;

}

struct WritePath {
  static void write(HitOutputData& data) {
    data.out << data.path << data.separator;
  }
};

struct DoNotWritePath {
  static void write(HitOutputData& data) {}
};

struct WriteContext {
  static void write(HitOutputData& data, const LG_SearchHit& searchHit) {
    data.writeContext(searchHit);
  }
};

struct NoContext {
  static void write(HitOutputData& data, const LG_SearchHit& searchHit) {}
};

TEST_CASE("callbackFn") {
  LG_HITCALLBACK_FN a = &callbackFn<WritePath, WriteContext, true>;
  LG_HITCALLBACK_FN b = &callbackFn<WritePath, NoContext, true>;
  LG_HITCALLBACK_FN c = &callbackFn<DoNotWritePath, NoContext, true>;
  LG_HITCALLBACK_FN d = &callbackFn<DoNotWritePath, WriteContext, true>;
  //LG_HITCALLBACK_FN d = &callbackFn<DoNotWritePath, NoContext, false>;

  LG_HITCALLBACK_FN arr[] = {a, b, c, d};

  bool shouldWritePath = true;
  bool shouldWriteContext = true;

  LG_HITCALLBACK_FN selection = arr[( 2*shouldWritePath ) + ( shouldWriteContext )];

}
