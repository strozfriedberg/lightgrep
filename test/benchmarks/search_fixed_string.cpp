#include <catch2/benchmark/catch_benchmark_all.hpp>
#include <catch2/catch_test_macros.hpp>

int sum_from(int begin, int end) {
	int sum = 0;
	for (int i = begin; i <= end; ++i) {
		sum += i;
	}
	return sum;
}

TEST_CASE("simple_test") {

	BENCHMARK("simple") {
		return sum_from(1, 20);
	};
}
