#include <iostream>
#include "tostring.h"
#include "date.h"
using namespace std;
using namespace cpp_lab3;

int main() {
	double d = 1.234;
	cpp_lab3::Date today;
	//string sd = toString(d);
	//string st = toString(today);
	//cout << "sd = " << sd << endl;
	//cout << "st = " << st << endl;
	toString(d);
}
