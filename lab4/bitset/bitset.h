/*
 * NOTE: uncomment the // lines when you have written the
 * BitsetIterator class.
 */

/*
 * A Bitset is an "array of bits", stored in a word (unsigned long).
 * The word contains BPW ("bits per word") bits.
 *
 * Bit 0 is in the least signficant position, bit BPW-1 in the most
 * significant position. Like this, for the set {0, 3, 30}:
 *
 *    01000000000000000000000000001001
 */

#ifndef BITSET_H
#define BITSET_H

#include <cstddef>  /* size_t */
#include <limits>   /* numeric_limits */

namespace cpp_lab4 {
    class BitReference;
    class BitsetIterator;
    
    class Bitset {
        friend class BitReference;
        friend class BitsetIterator;
    public:
        Bitset();
        BitReference operator[](size_t pos);    
        BitsetIterator begin();
        BitsetIterator end();
    private:
        typedef unsigned long BitStorage;
        BitStorage bits;
        static const size_t
            BPW = std::numeric_limits<BitStorage>::digits;
    };
}

#endif
