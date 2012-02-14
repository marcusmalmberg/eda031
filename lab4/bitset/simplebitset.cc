#include "simplebitset.h"

namespace cpp_lab4 {
    const size_t SimpleBitset::BPW;
    
    SimpleBitset::SimpleBitset() : bits(0) {}

    int SimpleBitset::size() const {
        return BPW;
    }

    bool SimpleBitset::get(size_t pos) const {
        /*
         * Shift a '1' to position pos, 'and' with the bits,
         * check if result is != 0.
         */
        return (bits & (1L << pos)) != 0;
    }

    void SimpleBitset::set(size_t pos, bool x) {
        /*
         * If x is true, shift a '1' to position pos, 'or' with
         * the bits, save the bits.
         * If x is false, shift a '1' to position pos, complement
         * so it becomes '0' and all other bits '1', 'and' with
         * the bits, save the bits.
         */
        if (x)
            bits |= 1L << pos;
        else
            bits &= ~ (1L << pos);
    }
}
