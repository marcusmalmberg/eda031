#include "bitsetiterator.h"

namespace cpp_lab4 {
	BitsetIterator& BitsetIterator::operator=(const BitsetIterator& bsi) {
		p_bits = bsi.p_bits;
		pos = bsi.pos;
		return *this;
	}
	
    bool BitsetIterator::operator!=(const BitsetIterator& bsi) const {
        //
        // *** IMPLEMENT ***
        //
        return true;
    }
    
    BitsetIterator& BitsetIterator::operator++() {
        //
        // *** IMPLEMENT ***
        //
        return *this;
    }
    
    BitReference BitsetIterator::operator*() {
        //
        // *** IMPLEMENT ***
        //
        return *this;
    }
}
