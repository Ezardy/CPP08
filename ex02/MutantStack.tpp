#ifndef EX02_MUTANTSTACK_TPP
#define EX02_MUTANTSTACK_TPP

#include <stack>

template<typename T, typename Container>
MutantStack<T, Container>::MutantStack(void) throw() : std::stack<T, Container>() {
}

template<typename T, typename Container>
MutantStack<T, Container>::MutantStack(Container const& cont) throw(std::bad_alloc)
	: std::stack<T, Container>(cont) {
}

template<typename T, typename Container>
MutantStack<T, Container>::MutantStack(MutantStack const& other) throw(std::bad_alloc)
	: std::stack<T, Container>(other) {
}

template<typename T, typename Container>
MutantStack<T, Container>::~MutantStack(void) throw() {
}

template<typename T, typename Container>
MutantStack<T, Container>& MutantStack<T, Container>::operator=(MutantStack const& other) throw(
	std::bad_alloc) {
	std::stack<T, Container>::operator=(other);
	return *this;
}

template<typename T, typename Container>
typename MutantStack<T, Container>::iterator MutantStack<T, Container>::begin(void) throw() {
	return std::stack<T, Container>::c.begin();
}

template<typename T, typename Container>
typename MutantStack<T, Container>::const_iterator MutantStack<T, Container>::begin(void) const
	throw() {
	return std::stack<T, Container>::c.begin();
}

template<typename T, typename Container>
typename MutantStack<T, Container>::reverse_iterator MutantStack<T, Container>::rbegin(
	void) throw() {
	return std::stack<T, Container>::c.rbegin();
}

template<typename T, typename Container>
typename MutantStack<T, Container>::const_reverse_iterator MutantStack<T, Container>::rbegin(
	void) const throw() {
	return std::stack<T, Container>::c.rbegin();
}

template<typename T, typename Container>
typename MutantStack<T, Container>::iterator MutantStack<T, Container>::end(void) throw() {
	return std::stack<T, Container>::c.end();
}

template<typename T, typename Container>
typename MutantStack<T, Container>::const_iterator MutantStack<T, Container>::end(void) const
	throw() {
	return std::stack<T, Container>::c.end();
}

template<typename T, typename Container>
typename MutantStack<T, Container>::reverse_iterator MutantStack<T, Container>::rend(void) throw() {
	return std::stack<T, Container>::c.rend();
}

template<typename T, typename Container>
typename MutantStack<T, Container>::const_reverse_iterator MutantStack<T, Container>::rend(
	void) const throw() {
	return std::stack<T, Container>::c.rend();
}

#endif
