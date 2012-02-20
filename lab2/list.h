/*
 * list.h
 */
#ifndef LIST_H
#define LIST_H

namespace cpp_lab1 {
    /*
     * List is a list of long integers
     */
    class List {
    public:
        /* create an empty list */
        List();
        
        /* destroy this list */
        ~List();
        
        /* insert d into this list as the first element */
        void insert(long d);
        
        /* remove the first element less than/equal to/greater than d,
           depending on the value of df. Do nothing if there is no value
           to remove. The public constants may be accessed with List::LESS,
           List::EQUAL, List::GREATER outside the class */
        enum DeleteFlag { LESS, EQUAL, GREATER };
        void remove(long d, DeleteFlag df = EQUAL);
        
        /* returns the size of the list */
        int size() const;
        
        /* returns true if the list is empty */
        bool empty() const;
        
        /* returns the value of the largest element in the list */
        long largest() const;
        
        /* print the contents of the list (for debugging) */
        void debugPrint() const;
            
    private:
        /* a list node */
        struct Node {
            long value;  // the node value
            Node* next;  // the pointer to the next node, 0 in the last node
            Node(long value = 0, Node* next = 0);
        };
        
        Node* head;      // the pointer to the head node, which contains
                         // a pointer to the first node
        
        /* forbid copying of lists */
        List(const List&);
        List& operator=(const List&);
    };
}

#endif

