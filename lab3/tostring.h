#ifndef TOSTRING_H
#define TOSTRING_H

#include <sstream>
#include <string>
#include "date.h"
using namespace std;

namespace cpp_lab3 {
	template <typename T>
	string toString(const T& obj) {
		ostringstream oss;
		oss << obj;
		return oss.str();
	}
}

#endif
