#include <string>
#include <iostream>
#include "vertexlist.h"
#include "vertex.h"

namespace cpp_lab2 {
    VertexList::VertexList() {}

    VertexList::~VertexList() {
        for (size_t i = 0; i < vptrs.size(); ++i) {
			vptrs[i]->adj.vptrs.clear();
		}
        for (size_t i = 0; i < vptrs.size(); ++i) {
			delete vptrs[i];
		}
    }
    
    void VertexList::add_vertex(const std::string& name) {
		if (VertexList::find(name) == 0) {
			VertexList::insert(new Vertex(name));
		}
	}   
    
    void VertexList::add_arc(const std::string& from, const std::string& to) {
		add_vertex(from);
		add_vertex(to);

    	Vertex *vFrom, *vTo;
		vFrom = VertexList::find(from);
		vTo = VertexList::find(to);
		vFrom->adj.insert(vTo);
	}
    
    std::stack<std::string> VertexList::top_sort() throw(cyclic) {
        for (size_t i = 0; i < vptrs.size(); ++i) {
			vptrs[i]->color = Vertex::WHITE;
		}
		std::stack<std::string> result;

        for (size_t i = 0; i < vptrs.size(); ++i) {
			if(vptrs[i]->color == Vertex::WHITE) {
				VertexList::dfs_visit(vptrs[i], result);
			}
		}
        return result;
    }
    
    void VertexList::debugPrint() const {
        using namespace std;
        cout << "VertexList, n = " << vptrs.size() << endl;
        for (size_t i = 0; i < vptrs.size(); ++i) {
            Vertex* v = vptrs[i];
            cout << "Vertex " << v->name << ". Adjacent: ";
            VertexList& vl = v->adj;
            for (size_t j = 0; j < vl.vptrs.size(); ++j)
                cout << vl.vptrs[j]->name << " ";
            cout << endl;
        }
    }

    void VertexList::insert(Vertex* v) {
		if(VertexList::find(v->name) == 0) {
			vptrs.push_back(v);
		}
    }
    
    Vertex* VertexList::find(const std::string& name) const {
		for (size_t i = 0; i < vptrs.size(); ++i) {
			if (vptrs[i]->name == name) {
				return vptrs[i];
			}
		}
		return 0;
    }
    
    void VertexList::dfs_visit(Vertex* v, std::stack<std::string>& result) throw(cyclic) {
    	v->color = Vertex::GRAY;
		std::vector<Vertex*> ad = v->adj.vptrs;
		for (size_t i = 0; i < ad.size(); ++i) {
			if (ad[i]->color == Vertex::WHITE) {
				VertexList::dfs_visit(ad[i], result);
			} else if (ad[i]->color == Vertex::GRAY) {
				throw cyclic();
			}
		}
		v->color = Vertex::BLACK;
		result.push(v->name);
	}
}
