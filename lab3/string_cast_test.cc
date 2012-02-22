#include <iostream>
#include "string_cast.cc"
#include "date.h"

using namespace std;
using namespace cpp_lab3;

int main() {
	try {
		int i = string_cast<int>("123");
		double d = string_cast<double>("12.34");
		Date date = string_cast<Date>("2011-01-10");
		cout << i << endl;
		cout << d << endl;
		cout << date << endl;
		cout << "All casts worked without any errors." << endl;
	} catch (StringCastException) {
		cout << "... error" << endl;
	}
}
