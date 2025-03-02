#ifndef EX01_SPAN_TPP
#define EX01_SPAN_TPP

#include <algorithm>
#include <cstddef>
#include <stdexcept>

template<typename It>
void Span::addRange(It beginIt, It endIt) throw(std::out_of_range) {
	std::size_t size = std::abs(endIt - beginIt);
	if (size) {
		if (size <= arr.size() - s) {
			std::copy(beginIt, endIt, arr.begin() + s);
			std::sort(arr.begin() + s, arr.begin() + s + size);
			std::inplace_merge(arr.begin(), arr.begin() + s, arr.begin() + s + size);
			s += size;
			changed = true;
		} else
			throw std::out_of_range("The range bigger than the Span vacant space");
	}
}

#endif
