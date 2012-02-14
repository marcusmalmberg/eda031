/*
 * A BitReference is a "pointer to a bit" in a Bitset. It
 * has a pointer to the word containing the bits (p_bits)
 * and an int (pos) which is the position of the bit in the word.
 *
 * A BitReference object is returned by operator[] in class
 * Bitset. The bit fiddling necessary to get or set a bit is
 * performed by the operators in this class.
 */

#ifndef BITSET_REFERENCE_H
#define BITSET_REFERENCE_H

#include "bitset.h"
#include <cstddef>

namespace cpp_lab4 {
    class BitReference {
    public:
        BitReference(Bitset::BitStorage* pb, size_t p)
            : p_bits(pb), pos(p) {}
        
        /*
         * This operator= is used for bs[i] = x.
         */
        BitReference& operator=(bool x);

        /*
         * This operator= is used for bs[i] = bs[j].
         */
        BitReference& operator=(const BitReference& br);

        /*
         * Operator bool() is used for x = bs[i].
         */
        operator bool() const;
    protected:
        Bitset::BitStorage* p_bits; // pointer to the word containing bits
        size_t pos;                 // position of the bit in the word
    };
}

#endif
