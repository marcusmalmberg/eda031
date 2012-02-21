#ifndef TOSTRING_H
#define TOSTRING_H

#include <sstream>
#include <string>
#include "date.h"

using namespace std;

template <typename T>
std::string toString(const T& obj);

template <typename T>
string toString(const T& obj) {
	ostringstream oss;
	oss << obj;
	return oss.str();
}


#endif
