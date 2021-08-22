#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include "../catch.hpp"
#include "../stest.h"


TEST_CASE("IPv4") {
  std::string ipNum("(1?[0-9]{1,2}|2([0-4][0-9]|5[0-5]))");
  std::string ipRE(ipNum + "(\\." + ipNum + "){3}");

  STest ipSearch(ipRE.c_str());

  BENCHMARK("localhost") {
    return ipSearch.search("127.0.0.1");
  };
  std::vector<SearchHit> e{{0, 9, 0}};
  REQUIRE(e == ipSearch.Hits);
  ipSearch.reset();

  BENCHMARK("logs") {
    return ipSearch.search(
      "192.168.198.92 - - [22/Dec/2002:23:08:37 -0400] \"GET / HTTP/1.1\" 200 6394 www.yahoo.com \"-\" \"Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1...)\" \"-\"\n"
      "192.168.198.92 - - [22/Dec/2002:23:08:38 -0400] \"GET /images/logo.gif HTTP/1.1\" 200 807 www.yahoo.com \"http://www.some.com/\" \"Mozilla/4.0 (compatible; MSIE 6...)\" \"-\"\n"
      "192.168.72.177 - - [22/Dec/2002:23:32:14 -0400] \"GET /news/sports.html HTTP/1.1\" 200 3500 www.yahoo.com \"http://www.some.com/\" \"Mozilla/4.0 (compatible; MSIE ...)\" \"-\"\n"
      "192.168.72.177 - - [22/Dec/2002:23:32:14 -0400] \"GET /favicon.ico HTTP/1.1\" 404 1997 www.yahoo.com \"-\" \"Mozilla/5.0 (Windows; U; Windows NT 5.1; rv:1.7.3)...\" \"-\"\n"
      "192.168.72.177 - - [22/Dec/2002:23:32:15 -0400] \"GET /style.css HTTP/1.1\" 200 4138 www.yahoo.com \"http://www.yahoo.com/index.html\" \"Mozilla/5.0 (Windows...\" \"-\"\n"
      "192.168.72.177 - - [22/Dec/2002:23:32:16 -0400] \"GET /js/ads.js HTTP/1.1\" 200 10229 www.yahoo.com \"http://www.search.com/index.html\" \"Mozilla/5.0 (Windows...\" \"-\"\n"
      "192.168.72.177 - - [22/Dec/2002:23:32:19 -0400] \"GET /search.php HTTP/1.1\" 400 1997 www.yahoo.com \"-\" \"Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; ...)\" \"-\"\n"
      "203.1.198.2 - - [22/Dec/2002:23:08:37 -0400] \"GET / HTTP/1.1\" 200 6394 www.yahoo.com \"-\" \"Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1...)\" \"-\"\n"
      "28.168.198.92 - - [22/Dec/2002:23:08:38 -0400] \"GET /images/logo.gif HTTP/1.1\" 200 807 www.yahoo.com \"http://www.some.com/\" \"Mozilla/4.0 (compatible; MSIE 6...)\" \"-\"\n"
      "1.168.72.177 - - [22/Dec/2002:23:32:14 -0400] \"GET /news/sports.html HTTP/1.1\" 200 3500 www.yahoo.com \"http://www.some.com/\" \"Mozilla/4.0 (compatible; MSIE ...)\" \"-\"\n"
      "2.68.72.77 - - [22/Dec/2002:23:32:14 -0400] \"GET /favicon.ico HTTP/1.1\" 404 1997 www.yahoo.com \"-\" \"Mozilla/5.0 (Windows; U; Windows NT 5.1; rv:1.7.3)...\" \"-\"\n"
      "9.18.2.17 - - [22/Dec/2002:23:32:15 -0400] \"GET /style.css HTTP/1.1\" 200 4138 www.yahoo.com \"http://www.yahoo.com/index.html\" \"Mozilla/5.0 (Windows...\" \"-\"\n"
      "17.8.72.1 - - [22/Dec/2002:23:32:16 -0400] \"GET /js/ads.js HTTP/1.1\" 200 10229 www.yahoo.com \"http://www.search.com/index.html\" \"Mozilla/5.0 (Windows...\" \"-\"\n"
      "192.168.72.177 - - [22/Dec/2002:23:32:19 -0400] \"GET /search.php HTTP/1.1\" 400 1997 www.yahoo.com \"-\" \"Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; ...)\" \"-\"\n"
    );
  };
  REQUIRE(14u == ipSearch.Hits.size());
  ipSearch.reset();
}

TEST_CASE("Huckleberry") {
  // A long fixed-string test, one with a few hits and one with none.
  // This is a best-case type search, so a good test of some possible optimizations.
  STest huckSearch("Huckleberry");

  std::string tom(
    "Shortly Tom came upon the juvenile pariah of the village, Huckleberry\n"
    "Finn, son of the town drunkard. Huckleberry was cordially hated and\n"
    "dreaded by all the mothers of the town, because he was idle and lawless\n"
    "and vulgar and bad--and because all their children admired him so, and\n"
    "delighted in his forbidden society, and wished they dared to be like\n"
    "him. Tom was like the rest of the respectable boys, in that he envied\n"
    "Huckleberry his gaudy outcast condition, and was under strict orders\n"
    "not to play with him. So he played with him every time he got a chance.\n"
    "Huckleberry was always dressed in the cast-off clothes of full-grown\n"
    "men, and they were in perennial bloom and fluttering with rags. His hat\n"
    "was a vast ruin with a wide crescent lopped out of its brim; his coat,\n"
    "when he wore one, hung nearly to his heels and had the rearward buttons\n"
    "far down the back; but one suspender supported his trousers; the seat\n"
    "of the trousers bagged low and contained nothing, the fringed legs\n"
    "dragged in the dirt when not rolled up.\n"
  );
  BENCHMARK("Tom Sawyer") {
    return huckSearch.search(tom);
  };
  REQUIRE(4u == huckSearch.Hits.size());

  std::string arthur(
    "When I told the king I was going out disguised as a petty freeman\n"
    "to scour the country and familiarize myself with the humbler life\n"
    "of the people, he was all afire with the novelty of the thing\n"
    "in a minute, and was bound to take a chance in the adventure\n"
    "himself--nothing should stop him--he would drop everything and\n"
    "go along--it was the prettiest idea he had run across for many\n"
    "a day.  He wanted to glide out the back way and start at once;\n"
    "but I showed him that that wouldn't answer.  You see, he was billed\n"
    "for the king's-evil--to touch for it, I mean--and it wouldn't be\n"
    "right to disappoint the house and it wouldn't make a delay worth\n"
    "considering, anyway, it was only a one-night stand.  And I thought\n"
    "he ought to tell the queen he was going away.  He clouded up at\n"
    "that and looked sad.  I was sorry I had spoken, especially when\n"
    "he said mournfully:\n"
  );
  huckSearch.reset();
  BENCHMARK("Connecticut Yankee") {
    return huckSearch.search(arthur);
  };
  REQUIRE(0u == huckSearch.Hits.size());
}
