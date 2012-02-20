#include <iostream>
#include <string>
#include <stack>
#include "graph.h"

using namespace cpp_lab2;
using namespace std;

/*
 * Test that a graph g is correctly built, and that the top_sort algorithm
 * is correct.
 */
void testGraph(Graph& g, bool isCyclic, const string& message) {
    cout << "--------------------------------------------------" << endl;
    cout << message << endl;
    cout << "Printout of the graph: " << endl;
    g.debugPrint();

    cout << "Computing topological order ..." << flush;
    try {
        stack<string> order = g.top_sort();
        cout << " done." << endl;
        cout << "A topological order is:" << endl;
        cout << "   ";
        while (! order.empty()) {
            cout << order.top() << " ";
            order.pop();
        }
        cout << endl;
    }
    catch (const cyclic&) {
        cout << endl;
        cout << "The top_sort() algorithm says that the graph is cyclic," 
            << endl;
        cout << "which is ";
        if (! isCyclic)
            cout << "NOT ";
        cout << "correct" << endl;
    }
    cout << endl;
}

int main() {
    Graph g1;
    g1.add_vertex("A");
    g1.add_vertex("B");
    g1.add_vertex("C");
    testGraph(g1, false, "A graph with unconnected vertices A, B, C\n" 
              "The topological order is ABC in any order");

    g1.add_arc("A", "B");
    g1.add_arc("B", "C");
    testGraph(g1, false, "A graph A->B->C. The topological order is ABC");
    
    g1.add_arc("C", "B");
    testGraph(g1, true, "The same graph with an added arc from C->B");
    
    Graph g2;
    g2.add_vertex("A");
    g2.add_vertex("B");
    g2.add_vertex("C");
    g2.add_vertex("D");
    g2.add_vertex("E");
    g2.add_arc("A", "B");
    g2.add_arc("C", "B");
    g2.add_arc("A", "D");
    g2.add_arc("D", "E");
    g2.add_arc("B", "E");
    testGraph(g2, false, "The example from the lab text");
    
    g2.add_arc("E", "C");
    testGraph(g2, true, "The same graph with an added arc from E->C");
}
