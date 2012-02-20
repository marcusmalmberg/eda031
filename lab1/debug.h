/*
 * debug.h
 *
 */

#ifndef DEBUG_H
#define DEBUG_H

/*
 * Assertions: called with assert(bool-expr). Abort execution
 * if the expression is false. Calls to assert() are removed
 * if NDEBUG is defined.
 *
 */
#include <cassert>

/*
 * Define the TRACE macro. TRACE("message") prints the message
 * on the terminal. Calls to TRACE are removed if NDEBUG is
 * defined.
 *
 */
#ifndef NDEBUG
#   include <iostream>
#   define TRACE(A) (std::clog << "---|trace|--> " << A << std::endl)
#else
#   define TRACE(A)
#endif

#endif

