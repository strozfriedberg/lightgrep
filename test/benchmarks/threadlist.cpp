#include <catch2/benchmark/catch_benchmark_all.hpp>
#include <catch2/catch_test_macros.hpp>

#include <list>

#include "ngstub.h"

namespace {

template<class T>
class stdlist: public std::list<T> {
public:
	void reserve(size_t) {}
};

template<class ListT, unsigned int INITIAL, unsigned int DELETE, unsigned int ADDITIONAL>
void list_mixed_benchmark(const char* name) {
	BENCHMARK(name) {
		ListT list;
		list.reserve(INITIAL * 2);
    for (unsigned int i = 0; i < INITIAL; ++i) {
      list.insert(list.begin(), ThreadNG{i, LG_SearchHit()});
    }
    auto itr = list.begin();
    for (unsigned int i = 0; i < DELETE; ++i) {
      itr = list.erase(itr);
      ++itr;
    }
    for (unsigned int i = 0; i < ADDITIONAL; ++i) {
      list.insert(list.begin(), ThreadNG{i, LG_SearchHit()});
    }
	};
}

TEST_CASE("threadlist") {
	list_mixed_benchmark<Threadlist, 5, 3, 2>("threadlist(5, 3, 2)");
	list_mixed_benchmark<stdlist<ThreadNG>, 5, 3, 2>("std::list(5, 3, 2)");
	list_mixed_benchmark<std::vector<ThreadNG>, 5, 3, 2>("std::vector(5, 3, 2)");

	list_mixed_benchmark<Threadlist, 10, 5, 3>("threadlist(10, 5, 3)");
	list_mixed_benchmark<stdlist<ThreadNG>, 10, 5, 3>("std::list(10, 5, 3)");
	list_mixed_benchmark<std::vector<ThreadNG>, 10, 5, 3>("std::vector(10, 5, 3)");

	list_mixed_benchmark<Threadlist, 30, 10, 10>("threadlist(30, 10, 10)");
	list_mixed_benchmark<stdlist<ThreadNG>, 30, 10, 10>("std::list(30, 10, 10)");
	list_mixed_benchmark<std::vector<ThreadNG>, 30, 10, 10>("std::vector(30, 10, 10)");
}
}
