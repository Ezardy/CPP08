#ifndef EX02_MUTANTSTACK_HPP
#define EX02_MUTANTSTACK_HPP

#include <new>
#include <queue>
#include <stack>

template<typename T, typename Container = std::deque<T> >
class MutantStack : public std::stack<T, Container> {
public:
	typedef typename Container::iterator			   iterator;
	typedef typename Container::reverse_iterator	   reverse_iterator;
	typedef typename Container::const_iterator		   const_iterator;
	typedef typename Container::const_reverse_iterator const_reverse_iterator;

	MutantStack(void) throw();
	explicit MutantStack(Container const& cont) throw(std::bad_alloc);
	MutantStack(MutantStack const& other) throw(std::bad_alloc);
	~MutantStack(void) throw();

	MutantStack& operator=(MutantStack const& other) throw(std::bad_alloc);

	iterator			   begin(void) throw();
	const_iterator		   begin(void) const throw();
	reverse_iterator	   rbegin(void) throw();
	const_reverse_iterator rbegin(void) const throw();
	iterator			   end(void) throw();
	const_iterator		   end(void) const throw();
	reverse_iterator	   rend(void) throw();
	const_reverse_iterator rend(void) const throw();
};

#include "MutantStack.tpp"
#endif
