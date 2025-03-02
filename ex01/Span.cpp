#include "Span.hpp"

#include <algorithm>
#include <numeric>
#include <stdexcept>

static unsigned abs_diff(int a, int b);

Span::Span(void) throw() : arr(), dist(), s(0), changed(true) {
}

Span::Span(unsigned n) throw(std::bad_alloc) : arr(n), dist(n), s(0), changed(true) {
}

Span::~Span(void) throw() {
}

Span& Span::operator=(Span const& other) throw(std::bad_alloc) {
	if (this != &other) {
		arr = other.arr;
		dist = other.dist;
		s = other.s;
		_shortestSpan = other._shortestSpan;
		changed = other.changed;
	}
	return *this;
}

Span::Span(Span const& other) throw(std::bad_alloc) {
	*this = other;
}

void Span::addNumber(int v) throw(std::out_of_range) {
	if (s < arr.size()) {
		arr[s] = v;
		std::inplace_merge(arr.begin(), arr.begin() + s, arr.begin() + s + 1);
		s += 1;
		changed = true;
	} else
		throw std::out_of_range("No vacant space for the number");
}

unsigned Span::shortestSpan(void) throw(std::out_of_range) {
	if (s < 2)
		throw std::out_of_range(
			"A Span object must have at least 2 numbers for shortest span calculation");
	else if (changed) {
		std::adjacent_difference(arr.begin(), arr.begin() + s, dist.begin(), abs_diff);
		_shortestSpan = *std::min_element(dist.begin() + 1, dist.begin() + s);
		changed = false;
	}
	return _shortestSpan;
}

unsigned Span::longestSpan(void) const throw(std::out_of_range) {
	if (s < 2)
		throw std::out_of_range(
			"A Span object must have at least 2 numbers for longest span calculation");
	else
		return arr[s - 1] - arr[0];
}

static unsigned abs_diff(int a, int b) {
	return a > b ? a - b : b - a;
}
