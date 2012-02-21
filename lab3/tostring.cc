#include <sstream>
#include "tostring.h"
using namespace std;

template <typename T>
string toString(const T& obj) {
	string out;
	stringstream(out) << obj;
	return out;
}
