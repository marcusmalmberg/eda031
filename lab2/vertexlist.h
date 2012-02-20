#ifndef VERTEXLIST_H
#define VERTEXLIST_H

#include <stack>
#include <string>
#include <vector>

namespace cpp_lab2 {
    class Vertex; // forward declaration
    
    struct cyclic {};   // exception type, the graph is cyclic
    
    /*
     * A VertexList is a dynamic list of vertices 
     */
    class VertexList {
    public:
        /* create an empty vertex list, destroy the list */
        VertexList();
        ~VertexList();
        
        /* insert a vertex with the label name in the list */
        void add_vertex(const std::string& name);
        
        /* insert an arc from the vertex from to the vertex to */
        void add_arc(const std::string& from, const std::string& to);
        
        /* return the vertex names in reverse topological order */
        std::stack<std::string> top_sort() throw(cyclic);
        
        /* print the vertex list (for debugging) */
        void debugPrint() const;
        
    private:
        void insert(Vertex* v);          // insert the vertex pointer v in vptrs,
                                         // if it's not already there
        Vertex* find(const std::string& name) const;  // return a pointer to the 
                                         // vertex named name, 0 if not found
        void dfs_visit(Vertex* v, std::stack<std::string>& result) throw(cyclic);
                                         // visit v in the traversal algorithm
        
        std::vector<Vertex*> vptrs;     // vector of pointers to vertices
        
        VertexList(const VertexList&);  // forbid copying
        VertexList& operator=(const VertexList&);
    };
}

#endif
