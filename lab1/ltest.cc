#include <iostream>
#include "list.h"
using namespace std;
using namespace cpp_lab1;

int main() {
	List l;
	cout << l.size() << endl;
	cout << l.empty() << endl;
	l.insert(1);
	cout << l.empty() << endl;
	l.insert(2);
	l.insert(4);
	l.insert(3);
	cout << l.size() << endl;
	cout << l.largest() << endl;
	l.debugPrint();
	l.remove(3, List::GREATER);
	l.debugPrint();
	l.remove(1, List::LESS);
	l.debugPrint();
	l.remove(0, List::EQUAL);
	l.debugPrint();
	l.remove(1, List::EQUAL);
	l.remove(3, List::LESS);
	l.remove(3, List::EQUAL);
	l.remove(3, List::EQUAL);
	cout << l.largest() << endl;
}
