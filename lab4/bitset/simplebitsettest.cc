#include "simplebitset.h"

#include <iostream>

using namespace std;
using namespace cpp_lab4;

/* Print the bitset bs */
void print(const SimpleBitset& bs) {
    for (int i = 0; i < bs.size(); ++i)
        cout << static_cast<int>(bs.get(i));
    cout << endl;
}

int main() {    
    // Define an empty bitset, set some bits, print the bitset
    SimpleBitset bs;
    bs.set(3, true);
    bs.set(0, bs.get(3));
    print(bs);
    
    // Clear a bit, use find the first set bit, clear this bit,
    // set the next bit, print the bitset
    bs.set(0, false);
    int pos = 0;
    while (pos < bs.size() && ! bs.get(pos))
        ++pos;
    if (pos < bs.size()) {
        bs.set(pos, false);
        ++pos;
        if (pos < bs.size()) 
            bs.set(pos, true);
    }
    print(bs);
}
