#ifndef STRING_CAST_H
#define STRING_CAST_H

#include <string>

struct StringCastException {};

template <typename T>
T string_cast(std::string s);

#endif
