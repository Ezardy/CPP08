#ifndef EX00_EASYFIND_TPP
#define EX00_EASYFIND_TPP

#include <algorithm>

template<typename T>
typename T::const_iterator easyfind(T const& cont, int e) {
	return std::find(cont.begin(), cont.end(), e);
}
#endif
