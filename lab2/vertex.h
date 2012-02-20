#ifndef VERTEX_H
#define VERTEX_H

#include <string>
#include "vertexlist.h"

namespace cpp_lab2 {
    /*
     * A Vertex contains the name of the vertex and a list of the
     * vertices that can be reached from this vertex 
     */
    class Vertex {
        friend class VertexList;
    private:
        /* create a vertex with name nm */
        Vertex(const std::string& nm);
        
        std::string name;  // name of the vertex
        VertexList adj;    // list of adjacent vertices
        enum Color { WHITE, GRAY, BLACK };
        Color color;       // used in the DFS algorithm
    };
}

#endif
