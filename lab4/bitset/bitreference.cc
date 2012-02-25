#include "bitreference.h"
#include "bitset.h"

#include <iostream>

namespace cpp_lab4 {
    BitReference& BitReference::operator=(bool x) {
		if(x) {
			*p_bits |= (1L << pos);
		} else {
			*p_bits &= ~(1L << pos);
		}
        return *this;
    }
    
    BitReference& BitReference::operator=(const BitReference& bsr) {
	
		bool x = ((*bsr.p_bits & (1L << bsr.pos)) != 0);
		if(x) {
			*p_bits |= (1L << pos);
		} else {
			*p_bits &= ~(1L << pos);
		}

        return *this;
    }
    
    BitReference::operator bool() const {
		return (*p_bits & (1L << pos)) != 0;
    }
}
