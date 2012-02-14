/*
 * A BitsetIterator is a BitReference with added operations that
 * makes it behave as an STL-compliant ForwardIterator (almost). 
 * Postfix ++, ==, and -> are not implemented.
 */

#ifndef BITSET_ITERATOR_H
#define BITSET_ITERATOR_H

#include "bitreference.h"
#include <iterator>

namespace cpp_lab4 {
    class BitsetIterator : public BitReference {
    public:
        /*
         * These typedefs are necessary to make the iterator STL-
         * compliant. Not too sure about if the definition of
         * 'reference' is correct, but it works with the test
         * program.
         */
        typedef bool          value_type;
        typedef int           difference_type;
        typedef BitReference  pointer;
        typedef BitReference& reference;
        typedef std::forward_iterator_tag iterator_category;
        
        BitsetIterator(Bitset::BitStorage* pb, size_t p)
            : BitReference(pb, p) {}
		BitsetIterator& operator=(const BitsetIterator& bsi);
        bool operator!=(const BitsetIterator& bsi) const;
        BitsetIterator& operator++();
        BitReference operator*();
    };
}

#endif
