#include "bitset.h"
#include <iostream>
#include "bitreference.h"

/*
 *       TEST, VERSION 1
 * There are two versions of the test program. The first version uses 
 * only operator[] and BitReferences. When this works, implement
 * the class BitsetIterator and use version 2 in bitsettest2.cc.
 *
 * Note that there is no way to get the size of a bitset, so we have
 * used 32 for the size. Not nice, but version 2 doesn't need the size.
 *
 */

int main() {
    using namespace std;
    using namespace cpp_lab4;
    
    // Define an empty bitset, set some bits, print the bitset
    Bitset bs;
    bs[3] = true;
    bs[0] = bs[3];
    for (int i = 0; i < 32; ++i)
        cout << static_cast<int>(bs[i]);
    cout << endl;
    
    // Clear a bit, find the first set
    // bit, clear this bit, set the next bit, print the bitset
    bs[0] = false;
    int pos = 0;
    while (pos < 32 && bs[pos] != true)
        ++pos;
    if (pos < 32) {
        bs[pos] = false;
        ++pos;
        if (pos < 32)
            bs[pos] = true;
    }
    for (int i = 0; i < 32; ++i)
        cout << static_cast<int>(bs[i]);
    cout << endl;
}
