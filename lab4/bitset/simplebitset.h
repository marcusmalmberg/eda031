/*
 * A SimpleBitset is an "array of bits", stored in a word (unsigned
 * long). The word contains BPW ("bits per word") bits.
 *
 * Bit 0 is in the least signficant position, bit BPW-1 in the most
 * significant position. Like this, for the set {0, 3, 30}:
 *
 *    01000000000000000000000000001001
 */

#ifndef SIMPLE_BITSET_H
#define SIMPLE_BITSET_H

#include <cstddef>  /* size_t */
#include <limits>   /* numeric_limits */

namespace cpp_lab4 {
    class SimpleBitset {
    public:
        SimpleBitset();
        int size() const;
        bool get(size_t pos) const;
        void set(size_t pos, bool x);
    private:
        typedef unsigned long BitStorage;
        BitStorage bits;
        static const size_t
            BPW = std::numeric_limits<BitStorage>::digits;
    };
}

#endif

