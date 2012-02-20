/*
 * list.cc
 */

#include <limits>
#include "list.h"
#include "debug.h"

/*
 * See debug.h for information on assert() and TRACE. Examples of use
 * are in the List destructor. Insert similar calls in other functions,
 * if you need them.
 *
 */

namespace cpp_lab1 {
    
    List::Node::Node(long v, Node* n) : value(v), next(n) {}
    
    List::List() : head(new Node) {}
    
    List::~List() {
        TRACE("List::~List()");
        assert(head != 0);
		Node* prev;
		Node* iter = head->next;
		while (iter != 0) {
			prev = iter;
			iter = iter->next;
			delete prev;
		}
    }
    
    void List::insert(long d) {
        TRACE("List::insert()");
		Node* n = new Node(d, head->next);
		head->next = n;
    }
    
    void List::remove(long d, DeleteFlag df) {
        TRACE("List::remove()");
		bool found = false;
		Node* prev = head;
		Node* iter = head->next;
		while (iter != 0 && !found) {
			switch (df) {
			case LESS:
				if (iter->value < d) found = true;
				break;
			case EQUAL:
				if (iter->value == d) found = true;
				break;
			case GREATER:
				if (iter->value > d) found = true;
				break;
			}
			if (!found) {
				prev = iter;
				iter = iter->next;
			}
		}
		if (found) {
			prev->next = iter->next;
			delete iter;
		}
    }
    
    int List::size() const {
        TRACE("List::size()");
        int size = 0;
		Node* iter = head;
		while (iter->next != 0) {
			iter = iter->next;
			size++;
		}
        return size;
    }
    
    bool List::empty() const {
        TRACE("List::empty()");
        bool empty = false;
		empty = head->next == 0;
        return empty;
    }
    
    long List::largest() const {
        TRACE("List::largest()");
        long largest = std::numeric_limits<long>::min();
		for (Node* iter = head; iter->next != 0; iter = iter->next) {
			largest = iter->value > largest ? iter->value : largest;
		}
        return largest;
    }
    
    void List::debugPrint() const {
#ifndef NDEBUG
        //-----------------------------------------------------------------
        // debugPrint() is used only during development, so we enclose the
        // code in this #ifndef block. The code will be removed when NDEBUG 
        // is defined.
        //
        // NDEBUG should be defined when compiling production release
        // versions. Use the -DNDEBUG option on the compiler command line.
        //-----------------------------------------------------------------
        for (Node* iter = head->next; iter != 0; iter = iter->next) {
            std::cout << iter->value << " ";
        }
        std::cout << std::endl;
#endif
    }
}

