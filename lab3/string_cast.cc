#include "string_cast.h"
using namespace std;

namespace cpp_lab3 {
	template <typename T>
	T string_cast(string s) {
		T obj(s);
		return obj;
	}
}
