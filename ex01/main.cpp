#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <deque>
#include <limits>
#include <list>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <vector>

#include "../test.hpp"
#include "Span.hpp"

static int generator(bool reset);
static int generate(void);

static bool Span_default_constructor(void);
static bool Span_constructor(void);
static bool Span_longestSpan(void);
static bool Span_shortestSpan(void);
static bool Span_copy_assignment(void);
static bool Span_copy_constructor(void);

int main() {
	bool   success = true;
	bool   (*tests[])(void) = {Span_default_constructor, Span_constructor,	   Span_longestSpan,
							   Span_shortestSpan,		 Span_copy_assignment, Span_copy_constructor};
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
TEST_START(Span_copy_constructor)
	TEST_LOGIC_START
		generator(true);
		Span	shuffledSpan(15000);
		std::vector<int>	arr(15000);
		std::generate(arr.begin(), arr.end(), generate);
		std::random_shuffle(arr.begin(), arr.end());
		shuffledSpan.addRange(arr.begin(), arr.end());
		unsigned	longestSpan = shuffledSpan.longestSpan();
		unsigned	shortestSpan = shuffledSpan.shortestSpan();

		Span	copySpan = shuffledSpan;
		TEST_ASSERT(copySpan.shortestSpan() == shortestSpan)
		TEST_ASSERT(copySpan.longestSpan() == longestSpan)
		TEST_EXCEPTION(copySpan.addNumber(1), std::out_of_range)
	TEST_LOGIC_END
	TEST_EMERGENCY_START
	TEST_EMERGENCY_END
TEST_END

TEST_START(Span_copy_assignment)
	TEST_LOGIC_START
		Span	defaultSpan(5);
		defaultSpan.addNumber(6);
		defaultSpan.addNumber(3);
		defaultSpan.addNumber(17);
		defaultSpan.addNumber(9);
		defaultSpan.addNumber(11);
		unsigned	longestSpan1 = defaultSpan.longestSpan();
		unsigned	shortestSpan1 = defaultSpan.shortestSpan();

		generator(true);
		Span	shuffledSpan(15000);
		std::vector<int>	arr(15000);
		std::generate(arr.begin(), arr.end(), generate);
		std::random_shuffle(arr.begin(), arr.end());
		shuffledSpan.addRange(arr.begin(), arr.end());
		unsigned	longestSpan2 = shuffledSpan.longestSpan();
		unsigned	shortestSpan2 = shuffledSpan.shortestSpan();

		Span	tmp;
		tmp = defaultSpan;
		defaultSpan = shuffledSpan;
		shuffledSpan = tmp;
		TEST_ASSERT(defaultSpan.longestSpan() == longestSpan2)
		TEST_ASSERT(defaultSpan.shortestSpan() == shortestSpan2)
		TEST_ASSERT(shuffledSpan.longestSpan() == longestSpan1)
		TEST_ASSERT(shuffledSpan.shortestSpan() == shortestSpan1)
		TEST_EXCEPTION(defaultSpan.addNumber(1), std::out_of_range)
		TEST_EXCEPTION(shuffledSpan.addNumber(1), std::out_of_range)
	TEST_LOGIC_END
	TEST_EMERGENCY_START
	TEST_EMERGENCY_END
TEST_END

struct Closest {
	Closest(int target) : t(target) {}

	bool operator()(int a, int b) { return std::abs(t - a) < std::abs(t - b); }

private:
	int t;
};

TEST_START(Span_shortestSpan)
	TEST_LOGIC_START
		Span	boundarySpan(2);
		boundarySpan.addNumber(std::numeric_limits<int>::min());
		boundarySpan.addNumber(std::numeric_limits<int>::max());
		TEST_ASSERT(boundarySpan.shortestSpan() == static_cast<unsigned>(std::numeric_limits<int>::max() - std::numeric_limits<int>::min()))
	
		Span	defaultSpan(5);
		TEST_EXCEPTION(defaultSpan.shortestSpan(), std::out_of_range)
		defaultSpan.addNumber(6);
		TEST_EXCEPTION(defaultSpan.shortestSpan(), std::out_of_range)
		defaultSpan.addNumber(3);
		TEST_ASSERT(defaultSpan.shortestSpan() == 3)
		defaultSpan.addNumber(17);
		defaultSpan.addNumber(9);
		defaultSpan.addNumber(11);
		TEST_ASSERT(defaultSpan.shortestSpan() == 2)
		
		Span				randomSpan(15000);
		std::vector<int>	set(15000);
		set[0] = rand();
		unsigned	currentSpan = std::numeric_limits<unsigned>::max();
		randomSpan.addNumber(set[0]);
		for (int i = 1; i < 15000; i += 1) {
			set[i] = rand();
			unsigned	s = std::abs(set[i] - *std::min_element(set.begin(), set.begin() + i, Closest(set[i])));
			if (s < currentSpan)
				currentSpan = s;
			randomSpan.addNumber(set[i]);
			TEST_ASSERT(currentSpan == randomSpan.shortestSpan())
		}

		Span	sameRandomSpan(15000);
		sameRandomSpan.addRange(set.begin(), set.end());
		TEST_ASSERT(sameRandomSpan.shortestSpan() == currentSpan)
	TEST_LOGIC_END
	TEST_EMERGENCY_START
	TEST_EMERGENCY_END
TEST_END

TEST_START(Span_longestSpan)
	TEST_LOGIC_START
		Span	tSpan(2);
		TEST_EXCEPTION(tSpan.longestSpan(), std::out_of_range)
		tSpan.addNumber(1);
		TEST_EXCEPTION(tSpan.longestSpan(), std::out_of_range)
		tSpan.addNumber(2);
		TEST_ASSERT(tSpan.longestSpan() == 1)
	
		Span				span(15002);
		std::vector<int>	arr(15000);
		std::generate(arr.begin(), arr.end(), generate);
		std::random_shuffle(arr.begin(), arr.begin() + 10000);
		std::random_shuffle(arr.begin() + 10000, arr.end());
		span.addRange(arr.begin(), arr.begin() + 10000);
		TEST_ASSERT(span.longestSpan() == 9999)
		span.addRange(arr.begin() + 10000, arr.end());
		TEST_ASSERT(span.longestSpan() == 14999)
		TEST_ASSERT(span.longestSpan() == 14999)
		TEST_ASSERT(span.longestSpan() == 14999)
		TEST_EXCEPTION(span.addRange(arr.begin(), arr.begin() + 3), std::out_of_range)
		span.addNumber(std::numeric_limits<int>::min());
		TEST_ASSERT(span.longestSpan() == static_cast<unsigned>(15000 - std::numeric_limits<int>::min()))
		span.addNumber(std::numeric_limits<int>::max());
		TEST_ASSERT(span.longestSpan() == std::numeric_limits<unsigned>::max())
		TEST_EXCEPTION(span.addNumber(0), std::out_of_range)
		TEST_ASSERT(span.longestSpan() == std::numeric_limits<unsigned>::max())
	TEST_LOGIC_END
	TEST_EMERGENCY_START
	TEST_EMERGENCY_END
TEST_END

TEST_START(Span_constructor)
	TEST_LOGIC_START
		const std::vector<int>	arr(5, 3);
		Span					zeroSpan(0);
		Span					span(5);

		zeroSpan.addRange(arr.begin(), arr.begin());
		TEST_EXCEPTION_MESSAGE(zeroSpan.addNumber(-3452), std::out_of_range, "No vacant space for the number")
		TEST_EXCEPTION_MESSAGE(zeroSpan.addRange(arr.begin(), arr.begin() + 1), std::out_of_range, "The range bigger than the Span vacant space")
		TEST_EXCEPTION_MESSAGE(zeroSpan.longestSpan(), std::out_of_range, "A Span object must have at least 2 numbers for longest span calculation")
		TEST_EXCEPTION_MESSAGE(zeroSpan.shortestSpan(), std::out_of_range, "A Span object must have at least 2 numbers for shortest span calculation")

		span.addNumber(arr[0]);
		TEST_EXCEPTION(span.shortestSpan(), std::out_of_range)
		TEST_EXCEPTION(span.longestSpan(), std::out_of_range)
		span.addNumber(arr[1]);
		span.longestSpan();
		span.shortestSpan();
		span.addRange(arr.begin() + 2, arr.end());
	TEST_LOGIC_END
	TEST_EMERGENCY_START
	TEST_EMERGENCY_END
TEST_END

TEST_START(Span_default_constructor)
	TEST_LOGIC_START
		const std::vector<int>	a(1, 0);
		Span					span;

		span.addRange(a.begin(), a.begin());
		TEST_EXCEPTION_MESSAGE(span.addNumber(-3452), std::out_of_range, "No vacant space for the number")
		TEST_EXCEPTION_MESSAGE(span.addRange(a.begin(), a.end()), std::out_of_range, "The range bigger than the Span vacant space")
		TEST_EXCEPTION_MESSAGE(span.longestSpan(), std::out_of_range, "A Span object must have at least 2 numbers for longest span calculation")
		TEST_EXCEPTION_MESSAGE(span.shortestSpan(), std::out_of_range, "A Span object must have at least 2 numbers for shortest span calculation")
	TEST_LOGIC_END
	TEST_EMERGENCY_START
	TEST_EMERGENCY_END
TEST_END
// clang-format on

static int generator(bool reset) {
	static int i = 0;

	if (reset)
		i = 0;
	else
		i += 1;
	return i;
}

static int generate(void) {
	return generator(false);
}
