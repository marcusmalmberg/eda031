#include "string_cast.h"
using namespace std;

template <typename T>
T string_cast(string s) {
	T obj(s);
	return obj;
}
