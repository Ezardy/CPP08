#include <algorithm>
#include <cstddef>
#include <deque>
#include <list>
#include <stack>
#include <streambuf>
#include <string>
#include <vector>

#include "../test.hpp"
#include "easyfind.hpp"

static int generator(void);

static bool easyfind_test(void);

int main() {
	bool   success = true;
	bool   (*tests[])(void) = {easyfind_test};
	size_t tests_count = sizeof(tests) / sizeof(tests[0]);
	for (size_t i = 0; success && i < tests_count; i += 1) {
		success = tests[i]();
		std::cout << '\n';
	}
	if (success)
		std::cout << "OK\n";
	return success;
}

// clang-format off
TEST_START(easyfind_test)
	TEST_LOGIC_START
		std::vector<int>	v(10000);

		std::generate(v.begin(), v.end(), generator);

		std::deque<int>		d(v.begin(), v.end());

		std::random_shuffle(v.begin(), v.end());

		std::list<int>		l(v.begin(), v.end());

		std::random_shuffle(v.begin(), v.end());
		std::random_shuffle(d.begin(), d.end());

		TEST_ASSERT(*easyfind(v, 5) == 5)
		TEST_ASSERT(*easyfind(v, 5761) == 5761)
		TEST_ASSERT(*easyfind(v, 0) == 0)

		TEST_ASSERT(*easyfind(l, 5) == 5)
		TEST_ASSERT(*easyfind(l, 5761) == 5761)
		TEST_ASSERT(*easyfind(l, 0) == 0)

		TEST_ASSERT(*easyfind(d, 5) == 5)
		TEST_ASSERT(*easyfind(d, 5761) == 5761)
		TEST_ASSERT(*easyfind(d, 0) == 0)
		TEST_LOGIC_END
	TEST_EMERGENCY_START
	TEST_EMERGENCY_END
TEST_END
// clang-format on

static int generator(void) {
	static int i = 0;
	return i++;
}
