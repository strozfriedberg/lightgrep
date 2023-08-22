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
      list.insert(list.begin(), ThreadNG());
    }
    auto itr = list.begin();
    for (unsigned int i = 0; i < DELETE; ++i) {
      itr = list.erase(itr);
      ++itr;
    }
    for (unsigned int i = 0; i < ADDITIONAL; ++i) {
      list.insert(list.begin(), ThreadNG());
    }
	};
}

template<class ListT, unsigned int LIST_SIZE, unsigned int ITERATIONS>
void list_iterate_append_swap(const char* name) {
	ListT one;
	ListT two;
	for (unsigned int i = 0; i < LIST_SIZE; ++i) {
		one.push_back(ThreadNG());
	}
	BENCHMARK(name) {
		uint64_t sum = 0;
		for (unsigned int i = 0; i < ITERATIONS; ++i) {
			for (auto itr(one.begin()); itr != one.end(); ++itr) {
				sum += itr->Start;
				two.push_back(*itr);
			}
			one.swap(two);
			two.clear();
		}
		REQUIRE(sum == 0);
	};
}

template<class ListT, unsigned int LIST_SIZE, unsigned int ITERATIONS>
void list_iterate_erase_append(const char* name) {
	ListT one;
	for (unsigned int i = 0; i < LIST_SIZE; ++i) {
		one.push_back(ThreadNG());
	}
	BENCHMARK(name) {
		uint64_t sum = 0;
		for (unsigned int i = 0; i < ITERATIONS - 1; ++i) {
			for (auto itr(one.begin()); itr != one.end(); ++itr) {
				sum += itr->Start;
			}
		}
		for (auto itr(one.begin()); itr != one.end(); ++itr) {
			sum += itr->Start;
			if (itr == one.begin()) {
				one.erase(itr);
			}
			one.push_back(ThreadNG());
		}
		REQUIRE(sum == 0);
	};
}

template<class ListT, unsigned int LIST_SIZE>
void list_iterate(const char* name) {
	ListT one;
	for (unsigned int i = 0; i < LIST_SIZE; ++i) {
		one.push_back(ThreadNG());
	}
	BENCHMARK(name) {
		unsigned int sum = 0;
		for (auto& t: one) {
			sum += t.Start;
		}
		return sum;
	};
}

TEST_CASE("threadlist") {
	list_mixed_benchmark<Fastlist<ThreadNG>, 5, 3, 2>("threadlist(5, 3, 2)");
	list_mixed_benchmark<stdlist<ThreadNG>, 5, 3, 2>("std::list(5, 3, 2)");
	list_mixed_benchmark<std::vector<ThreadNG>, 5, 3, 2>("std::vector(5, 3, 2)");

	list_mixed_benchmark<Fastlist<ThreadNG>, 10, 5, 3>("threadlist(10, 5, 3)");
	list_mixed_benchmark<stdlist<ThreadNG>, 10, 5, 3>("std::list(10, 5, 3)");
	list_mixed_benchmark<std::vector<ThreadNG>, 10, 5, 3>("std::vector(10, 5, 3)");

	list_mixed_benchmark<Fastlist<ThreadNG>, 30, 10, 10>("threadlist(30, 10, 10)");
	list_mixed_benchmark<stdlist<ThreadNG>, 30, 10, 10>("std::list(30, 10, 10)");
	list_mixed_benchmark<std::vector<ThreadNG>, 30, 10, 10>("std::vector(30, 10, 10)");

	list_iterate_append_swap<Fastlist<ThreadNG>, 1, 20>("TL iter swap(1, 20)");
	list_iterate_append_swap<std::list<ThreadNG>, 1, 20>("std::list iter swap(1, 20)");
	list_iterate_append_swap<std::vector<ThreadNG>, 1, 20>("std::vector iter swap(1, 20)");
	list_iterate_erase_append<Fastlist<ThreadNG>, 1, 20>("TL iter append(1, 20)");

	list_iterate_append_swap<Fastlist<ThreadNG>, 5, 20>("TL iter swap(5, 20)");
	list_iterate_append_swap<std::list<ThreadNG>, 5, 20>("std::list iter swap(5, 20)");
	list_iterate_append_swap<std::vector<ThreadNG>, 5, 20>("std::vector iter swap(5, 20)");
	list_iterate_erase_append<Fastlist<ThreadNG>, 5, 20>("TL iter append(5, 20)");

	list_iterate_append_swap<Fastlist<ThreadNG>, 10, 40>("TL iter swap(10, 40)");
	list_iterate_append_swap<std::list<ThreadNG>, 10, 40>("std::list iter swap(10, 40)");
	list_iterate_append_swap<std::vector<ThreadNG>, 10, 40>("std::vector iter swap(10, 40)");
	list_iterate_erase_append<Fastlist<ThreadNG>, 5, 20>("TL iter append(10, 40)");

	list_iterate<Fastlist<ThreadNG>, 5>("fastlist_iter(5)");
	list_iterate<std::list<ThreadNG>, 5>("std::list_iter(5)");
	list_iterate<std::vector<ThreadNG>, 5>("std::vector_iter(5)");
	list_iterate<Fastlist<ThreadNG>, 20>("fastlist_iter(20)");
	list_iterate<std::list<ThreadNG>, 20>("std::list_iter(20)");
	list_iterate<std::vector<ThreadNG>, 20>("std::vector_iter(20)");
	list_iterate<Fastlist<ThreadNG>, 50>("fastlist_iter(50)");
	list_iterate<std::list<ThreadNG>, 50>("std::list_iter(50)");
	list_iterate<std::vector<ThreadNG>, 50>("std::vector_iter(50)");
	list_iterate<Fastlist<ThreadNG>, 1000>("fastlist_iter(1000)");
	list_iterate<std::list<ThreadNG>, 1000>("std::list_iter(1000)");
	list_iterate<std::vector<ThreadNG>, 1000>("std::vector_iter(1000)");
	list_iterate<Fastlist<ThreadNG>, 1000000>("fastlist_iter(1000000)");
	list_iterate<std::list<ThreadNG>, 1000000>("std::list_iter(1000000)");
	list_iterate<std::vector<ThreadNG>, 1000000>("std::vector_iter(1000000)");
}

}
