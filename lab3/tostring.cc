#include <sstream>
#include "tostring.h"
using namespace std;

namespace cpp_lab3 {
	template <typename T>
	string toString(const T& obj) {
		string out;
		stringstream(out) << obj;
		return out;
	}
}
