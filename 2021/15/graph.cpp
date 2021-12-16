#include <list>
#include "graph.h"
using namespace std;


Vertex::Vertex() {

}

Vertex::Vertex(int i, int j) {
    iloc = i;
    jloc = j;
}

bool Vertex::operator==(const Vertex& v) {
    return iloc == v.iloc && jloc == v.jloc;
}

Edge::Edge(Vertex* s, Vertex* e, int w) {
    start = s;
    end = e;
    weight = w;
}

void Graph::add_edge(Edge e) {
    edges.push_back(e);
}

void Graph::add_vertex(Vertex v) {
    vertices.push_back(v);
}

list<Edge> Graph::neighb_edges(Vertex v) {
    list<Edge> neighb;
    for (Edge e : edges) {
        if (*e.start == v) {
            neighb.push_back(e);
        }
    }
    return neighb;
}