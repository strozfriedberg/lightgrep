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
