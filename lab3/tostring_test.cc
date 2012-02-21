#include <iostream>
#include "tostring.h"
#include "date.h"
using namespace std;

int main() {
	double d = 1.234;
	cpp_lab3::Date today;
	cout << "Today: " << today << endl;
	string sd = toString(d);
	string st = toString(today);
	cout << "sd = " << sd << endl;
	cout << "st = " << st << endl;
	toString(d);
}
