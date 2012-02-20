/*
 * A program containing many common programming errors, to test
 * valgrind.
 *
 */
#include <iostream>
#include <vector>

using namespace std;

/*
 * Use uninitalized variable.
 */
void test1() {
    int x;
    int y = x;
    cout << y << endl;
}

/*
 * Dereference null pointer.
 */
void test2() {
    int *x = 0;
    cout << *x << endl;
}

/*
 * IMPLEMENT more methods!
 */
void test3() {
	int v[10];
	v[10] = 0;
}

int main() {
    cout << "Test # ";
    int nbr;
    cin >> nbr;
    switch (nbr) {
        case 1: test1(); break;
        case 2: test2(); break;
        case 3: test3(); break;
        default: cout << "No such test" << endl;
    }
}
