#include "bitset.h"
#include <iostream>
#include "bitreference.h"
#include "bitsetiterator.h"
#include <algorithm>

/*
 *       TEST, VERSION 2
 * This version of the test program uses iterators.
 *
 */

int main() {
    using namespace std;
    using namespace cpp_lab4;
    
    // Define an empty bitset, set some bits, print the bitset
    Bitset bs;
    bs[3] = true;
    bs[0] = bs[3];
    copy(bs.begin(), bs.end(), ostream_iterator<int>(cout));
    cout << endl;
    
    // Clear a bit, use the STL find algorithm to find the first set
    // bit, clear this bit, set the next bit, print the bitset
    bs[0] = false;    
    BitsetIterator it = find(bs.begin(), bs.end(), true);
    if (it != bs.end()) {
        *it = false;
        ++it;
        if (it != bs.end())
            *it = true;
    }
    copy(bs.begin(), bs.end(), ostream_iterator<int>(cout));
    cout << endl;   
}
