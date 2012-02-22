#ifndef STRING_CAST_H
#define STRING_CAST_H
  
#include <sstream>
#include <string>
using namespace std;

namespace cpp_lab3 {
	struct StringCastException {};

	template <typename T>
	T string_cast(string s) {
		istringstream buff(s);
		T obj;
		buff >> obj;
		return obj;
	}
}

#endif
