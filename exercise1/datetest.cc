#include <iostream>
#include "date.h"

using namespace std;

/*
 * Prints the date d in the format yyyy-mm-dd. The function is intended to
 * show an example of a global function; it would be better to overload
 * the output operator <<.
 */
void print(const Date& d) {
    cout << d.getYear() << "-";
    if (d.getMonth() < 10)
        cout << "0";
    cout << d.getMonth() << "-";
    if (d.getDay() < 10)
        cout << "0";
    cout << d.getDay();
}

int main() {
    // Check 'next' by creating an object describing today's date, then
    // printing dates more than a month ahead
    cout << "--- Today and more than a month ahead" << endl;
    Date d1;
    print(d1);
    cout << endl;
    for (int i = 1; i <= 35 ; ++i) {
        d1.next();
        print(d1);
        cout << endl;
    }
	
    // Check so 'next' functions correctly from one year to the next
    cout << "--- New Year's Eve and the next day" << endl;
    Date d2(2005,12,31);
    print(d2);
    cout << endl;
    d2.next();
    print(d2);
    cout << endl;
}

