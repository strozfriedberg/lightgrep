#include <catch2/catch_test_macros.hpp>

#include "parsetree.h"

TEST_CASE("nodesUpperBound_alpha") {
  REQUIRE(nodesUpperBound("abcd") == 8);
}

TEST_CASE("nodesUpperBound_quantifiers") {
  REQUIRE(nodesUpperBound("a+b*c?d") == 14);
}

TEST_CASE("nodesUpperBound_line_start_anchor") {
  REQUIRE(nodesUpperBound("^a") == 5);
}

TEST_CASE("nodesUpperBound_line_end_anchor") {
  REQUIRE(nodesUpperBound("a$") == 5);
}

TEST_CASE("nodesUpperBound_many_anchors") {
  // Weird, but not illegal
  REQUIRE(nodesUpperBound("\\W^^^^^\\W") == 23);
}

TEST_CASE("nodesUpperBound_whack_b") {
  REQUIRE(nodesUpperBound("\\b") == 10);
}

TEST_CASE("nodesUpperBound_whack_B") {
  REQUIRE(nodesUpperBound("\\B") == 10);
}
