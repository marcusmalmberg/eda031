#include "bitreference.h"
#include "bitset.h"

namespace cpp_lab4 {
    BitReference& BitReference::operator=(bool x) {
        //
        // *** IMPLEMENT ***
        // Note that this corresponds to the set() function in SimpleBitset.
        //
        return *this;
    }
    
    BitReference& BitReference::operator=(const BitReference& bsr) {
        //
        // *** IMPLEMENT ***
        //
        return *this;
    }
    
    BitReference::operator bool() const {
        //
        // *** IMPLEMENT ***
        // Note that this corresponds to the get() function in SimpleBitset.
        //
        return false;
    }
}
