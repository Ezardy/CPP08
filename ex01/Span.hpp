#ifndef EX01_SPAN_HPP
#define EX01_SPAN_HPP

#include <new>
#include <stdexcept>
#include <vector>

class Span {
public:
	Span(void) throw();
	Span(unsigned n) throw(std::bad_alloc);
	Span(Span const& other) throw(std::bad_alloc);
	~Span(void) throw();

	Span& operator=(Span const& other) throw(std::bad_alloc);

	void addNumber(int v) throw(std::out_of_range);

	template<typename It>
	void addRange(It beginIt, It endIt) throw(std::out_of_range);

	unsigned shortestSpan(void) throw(std::out_of_range);
	unsigned longestSpan(void) const throw(std::out_of_range);

private:
	std::vector<int>	  arr;
	std::vector<unsigned> dist;
	unsigned			  s;
	unsigned			  _shortestSpan;
	bool				  changed;
};

#include "Span.tpp"
#endif
