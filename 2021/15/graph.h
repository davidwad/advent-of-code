#include <list>
using namespace std;

class Vertex {
    public:
        int iloc;
        int jloc;
        Vertex* pred;
        int d = __INT32_MAX__/2;
        Vertex();
        Vertex(int i, int j);
        bool operator==(const Vertex& v);
};

class Edge {
    public:
        Vertex* start;
        Vertex* end;
        int weight;

        Edge(Vertex* s, Vertex* e, int w);
};

class Graph {
    public:
        list<Edge> edges;
        list<Vertex> vertices;

        void add_edge(Edge e);
        void add_vertex(Vertex v);
        list<Edge> neighb_edges(Vertex v);
};