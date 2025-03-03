#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <deque>
#include <iterator>
#include <list>
#include <string>
#include <vector>

#include "../test.hpp"
#include "MutantStack.hpp"

static bool MutantStack_default_constructor(void);
static bool MutantStack_constructor(void);
static bool MutantStack_copy_constructor(void);
static bool MutantStack_copy_assignment(void);
static bool MutantStack_iterators(void);

static int	generator(bool reset);
static int	generate(void);
static void inc(int& a);

int main() {
	bool   success = true;
	bool   (*tests[])(void) = {MutantStack_default_constructor, MutantStack_constructor,
							   MutantStack_copy_constructor, MutantStack_copy_assignment,
							   MutantStack_iterators};
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
TEST_START(MutantStack_iterators)
	TEST_LOGIC_START
		std::vector<int>	v(15000);
		std::generate(v.begin(), v.end(), generate);

		MutantStack<int>					ds;
		MutantStack<int, std::vector<int> >	vs;
		MutantStack<int, std::list<int> >	ls;

		for (std::vector<int>::const_iterator it = v.begin(); it !=v.end(); ++it) {
			ds.push(*it);
			vs.push(*it);
			ls.push(*it);
		}

		MutantStack<int>::const_iterator	dit = ds.begin();
		for (std::vector<int>::const_iterator it = v.begin(); it != v.end(); ++it, ++dit)
			TEST_ASSERT(*it == *dit)
		MutantStack<int>::const_reverse_iterator	rdit = ds.rbegin();
		for (std::vector<int>::const_reverse_iterator it = v.rbegin(); it != v.rend(); ++it, ++rdit)
			TEST_ASSERT(*it == *rdit)

		MutantStack<int, std::vector<int> >::const_iterator	vit = vs.begin();
		for (std::vector<int>::const_iterator it = v.begin(); it != v.end(); ++it, ++vit)
			TEST_ASSERT(*it == *vit)
		MutantStack<int, std::vector<int> >::const_reverse_iterator	rvit = vs.rbegin();
		for (std::vector<int>::const_reverse_iterator it = v.rbegin(); it != v.rend(); ++it, ++rvit)
			TEST_ASSERT(*it == *rvit)

		MutantStack<int, std::list<int> >::const_iterator	lit = ls.begin();
		for (std::vector<int>::const_iterator it = v.begin(); it != v.end(); ++it, ++lit)
			TEST_ASSERT(*it == *lit)
		MutantStack<int, std::list<int> >::const_reverse_iterator	rlit = ls.rbegin();
		for (std::vector<int>::const_reverse_iterator it = v.rbegin(); it != v.rend(); ++it, ++rlit)
			TEST_ASSERT(*it == *rlit)

		*ds.rbegin() = -1234;
		TEST_ASSERT(ds.top() == -1234)
		*(ds.begin() + 14999) = -45;
		TEST_ASSERT(ds.top() == -45)
		*(ds.end() - 1) = -5;
		TEST_ASSERT(ds.top() == -5)
		*(ds.rend() - 15000) = -6;
		TEST_ASSERT(ds.top() == -6)

		*vs.rbegin() = -1234;
		TEST_ASSERT(vs.top() == -1234)
		*(vs.begin() + 14999) = -45;
		TEST_ASSERT(vs.top() == -45)
		*(vs.end() - 1) = -5;
		TEST_ASSERT(vs.top() == -5)
		*(vs.rend() - 15000) = -6;
		TEST_ASSERT(vs.top() == -6)

		MutantStack<int, std::list<int> >::iterator	lend = ls.end();
		*--lend = -1234;
		TEST_ASSERT(ls.top() == -1234)
		MutantStack<int, std::list<int> >::reverse_iterator	reit = ls.rend();
		std::advance(reit, -15000);
		*reit = -45;
		TEST_ASSERT(ls.top() == -45)
		*ls.rbegin() = -5;
		TEST_ASSERT(ls.top() == -5)
		MutantStack<int, std::list<int> >::iterator	beit = ls.begin();
		std::advance(beit, 14999);
		*beit = -6;
		TEST_ASSERT(ls.top() == -6)
	TEST_LOGIC_END
	TEST_EMERGENCY_START
	TEST_EMERGENCY_END
TEST_END

TEST_START(MutantStack_copy_assignment)
	TEST_LOGIC_START
		std::vector<int>	v(15000);
		std::generate(v.begin(), v.end(), generate);
		std::list<int>		l(v.begin(), v.end());
		std::random_shuffle(v.begin(), v.end());
		std::deque<int>		d(v.begin(), v.end());
		std::random_shuffle(v.begin(), v.end());

		MutantStack<int>					ds(d);
		MutantStack<int, std::vector<int> >	vs(v);
		MutantStack<int, std::list<int> >	ls(l);

		MutantStack<int>					dsCopy;
		MutantStack<int, std::vector<int> >	vsCopy;
		MutantStack<int, std::list<int> >	lsCopy;

		TEST_ASSERT(dsCopy.empty() && !ds.empty() && vsCopy.empty() && !vs.empty() && lsCopy.empty() && !ls.empty())

		dsCopy = ds;
		vsCopy = vs;
		lsCopy = ls;

		for (; !dsCopy.empty(); dsCopy.pop(), ds.pop())
			TEST_ASSERT(dsCopy.top() == ds.top())
		TEST_ASSERT(ds.empty())
		for (; !vsCopy.empty(); vsCopy.pop(), vs.pop())
			TEST_ASSERT(vsCopy.top() == vs.top())
		TEST_ASSERT(vs.empty())
		for (; !lsCopy.empty(); lsCopy.pop(), ls.pop())
			TEST_ASSERT(lsCopy.top() == ls.top())
		TEST_ASSERT(ls.empty())
	TEST_LOGIC_END
	TEST_EMERGENCY_START
	TEST_EMERGENCY_END
TEST_END

TEST_START(MutantStack_copy_constructor)
	TEST_LOGIC_START
		std::vector<int>	v(15000);
		std::generate(v.begin(), v.end(), generate);
		std::list<int>		l(v.begin(), v.end());
		std::random_shuffle(v.begin(), v.end());
		std::deque<int>		d(v.begin(), v.end());
		std::random_shuffle(v.begin(), v.end());

		MutantStack<int>					ds(d);
		MutantStack<int, std::vector<int> >	vs(v);
		MutantStack<int, std::list<int> >	ls(l);

		MutantStack<int>					dsCopy(ds);
		MutantStack<int, std::vector<int> >	vsCopy(vs);
		MutantStack<int, std::list<int> >	lsCopy(ls);

		for (; !dsCopy.empty(); dsCopy.pop(), ds.pop())
			TEST_ASSERT(dsCopy.top() == ds.top())
		TEST_ASSERT(ds.empty())
		for (; !vsCopy.empty(); vsCopy.pop(), vs.pop())
			TEST_ASSERT(vsCopy.top() == vs.top())
		TEST_ASSERT(vs.empty())
		for (; !lsCopy.empty(); lsCopy.pop(), ls.pop())
			TEST_ASSERT(lsCopy.top() == ls.top())
		TEST_ASSERT(ls.empty())
	TEST_LOGIC_END
	TEST_EMERGENCY_START
	TEST_EMERGENCY_END
TEST_END

TEST_START(MutantStack_constructor)
	TEST_LOGIC_START
		std::vector<int>	vec(15000);
		std::generate(vec.begin(), vec.end(), generate);
		std::list<int>		lis(vec.begin(), vec.end());
		std::deque<int>		que(vec.begin(), vec.end());
		
		MutantStack<int, std::vector<int> >	vecStack(vec);
		MutantStack<int, std::list<int> >	lisStack(lis);
		MutantStack<int, std::deque<int> >	queStack(que);
		std::for_each(vec.begin(), vec.end(), inc);
		std::for_each(lis.begin(), lis.end(), inc);
		std::for_each(lis.begin(), lis.end(), inc);
		std::for_each(que.begin(), que.end(), inc);
		std::for_each(que.begin(), que.end(), inc);
		std::for_each(que.begin(), que.end(), inc);
		std::vector<int>::const_reverse_iterator vit = vec.rbegin();
		std::list<int>::const_reverse_iterator lit = lis.rbegin();
		std::deque<int>::const_reverse_iterator qit = que.rbegin();
		for (; vit != vec.rend(); ++vit, ++lit, ++qit, vecStack.pop(), lisStack.pop(), queStack.pop())
			TEST_ASSERT((*vit == vecStack.top() + 1) && (*lit == lisStack.top() + 2) && (*qit == queStack.top() + 3))
		TEST_ASSERT(vecStack.empty() && lisStack.empty() && queStack.empty())
	TEST_LOGIC_END
	TEST_EMERGENCY_START
	TEST_EMERGENCY_END
TEST_END

TEST_START(MutantStack_default_constructor)
	TEST_LOGIC_START
		MutantStack<int>	emptyInt;
		TEST_ASSERT(emptyInt.empty())
		TEST_ASSERT(emptyInt.begin() == emptyInt.end())
		int const	ia[] = {1, 2, 3};
		for (unsigned i = 0; i < sizeof(ia) / sizeof(int); i += 1)
			emptyInt.push(ia[i]);
		for (unsigned i = emptyInt.size(); !emptyInt.empty(); emptyInt.pop())
			TEST_ASSERT(emptyInt.top() == ia[--i])

		MutantStack<std::string>	emptyString;
		TEST_ASSERT(emptyString.empty())
		TEST_ASSERT(emptyString.begin() == emptyString.end())
		std::string const	sa[] = {"one", "two", "three"};
		for (unsigned i = 0; i < sizeof(sa) / sizeof(std::string); i += 1)
			emptyString.push(sa[i]);
		for (unsigned i = emptyString.size(); !emptyString.empty(); emptyString.pop())
			TEST_ASSERT(emptyString.top() == sa[--i])
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

static void inc(int& a) {
	a += 1;
}
