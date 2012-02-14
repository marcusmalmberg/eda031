/*
 * NOTE: remove the comments when you have written the
 * BitsetIterator class.
 */

#include "bitset.h"
#include "bitreference.h"
//#include "bitsetiterator.h"

namespace cpp_lab4 {
    const size_t Bitset::BPW;
    
    Bitset::Bitset() : bits(0) {}
    
    BitReference Bitset::operator[](size_t pos) {
        return BitReference(&bits, pos);
    }
    
    /*
     * Uncomment the following function definitions when you 
     * have written the BitsetIterator class.
     */
    /*
    BitsetIterator Bitset::begin() {
        //
        // *** IMPLEMENT ***
        //
    }
    
    BitsetIterator Bitset::end() {
        //
        // *** IMPLEMENT ***
        //
    }
     */
}
