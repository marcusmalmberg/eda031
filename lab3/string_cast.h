#ifndef STRING_CAST_H
#define STRING_CAST_H

#include <string>

namespace cpp_lab3 {
	struct StringCastException {};

	template <typename T>
	T string_cast(std::string s);
}

#endif
