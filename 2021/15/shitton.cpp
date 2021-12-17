
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <queue>
#include <vector>
#include <set>
#include <map>
#include <chrono>
#include "graph.h"
using namespace std;


class VertexQCmp {
    public:
        bool operator() (const Vertex v1, const Vertex v2) const {
            return v1.d > v2.d;
        }
};

bool inside_grid(int i, int j, int gridsize) {
    return i >= 0 && j >= 0 && i < gridsize && j < gridsize;
}

bool exists(Vertex vertex, list<Vertex> vertices) {
    for (Vertex v : vertices) {
        if (v == vertex) { return true; }
    }
    return false;
}

int transform(int w, int gi, int gj) {
    for (int k = 0; k < gi+gj; k++) {
        w = (w + 1) % 10;
        if (w == 0) { w = 1; }
    }
    return w;
}

void print_vertex(Vertex v) {
    cout << v.iloc << ',' << v.jloc << ',' << v.d << '\n';
}

void print_graph(Graph G) {
    for (Vertex v : G.vertices) {
        cout << "Vertex: ";
        print_vertex(v);
        for (Edge e : G.neighb_edges(v)) {
            cout << "\tNeighbour: ";
            print_vertex(*e.end);
        }
    }
}

list<Vertex> dijkstra(Graph G, Vertex s, Vertex t, int gridsize) {
    list<Vertex> S;
    int done[gridsize][gridsize] = {0};
    priority_queue<Vertex,vector<Vertex>,VertexQCmp> Q;
    int old[gridsize][gridsize] = {INT32_MAX};

    for (Vertex v : G.vertices) {
        if (v == s) {
            v.d = 0;
        }
        Q.push(v);
    }
    int n = 0;
    while (!Q.empty()) {
        cout << n << '\n';
        Vertex u = Q.top();
        Q.pop();
        S.push_back(u);
        if (u == t) { break; }
        done[u.iloc][u.jloc] = 1;
        for (Edge e : G.neighb_edges(u)) {
            Vertex* v = e.end;
            int w = e.weight;
            if (!done[v->iloc][v->jloc]) {
                if (u.d + w < v->d) {
                    v->d = u.d + w;
                    v->pred = &u;
                    Q.push(*v);
                }
            }

        }
        n++;
    }
    return S;
}


int main() {
    const int subsize = 100;
    const int gridsize = subsize * 5;

    ifstream input("input.txt");
    string line;
    int subweights[subsize][subsize];
    int weights[gridsize][gridsize];
    vector<vector<Vertex>> vertices;
    Graph G;

    for (int i=0; i<subsize; i++) {
        getline(input, line);
        for (int j=0; j<subsize; j++) {
            subweights[i][j] = line[j] - '0';
        }
    }

    for (int gi=0; gi<5; gi++) {
        for (int gj=0; gj<5; gj++) {
            for (int i=0; i<subsize; i++) {
                for (int j=0; j<subsize; j++) {
                    int iloc = gi*subsize + i;
                    int jloc = gj*subsize + j;
                    weights[iloc][jloc] = transform(subweights[i][j], gi, gj);
                }
            }
        }
    }

    for (int i=0; i<gridsize; i++) {
        vector<Vertex> vrow;
        for (int j=0; j<gridsize; j++) {
            Vertex v(i, j);
            vrow.push_back(v);
            G.add_vertex(v);
        }
        vertices.push_back(vrow);
    }

    for (int i=0; i<gridsize; i++) {
        for (int j=0; j<gridsize; j++) {
            int vi[4] = {i-1, i, i, i+1};
            int vj[4] = {j, j-1, j+1, j};
            for (int k=0; k<4; k++) {
                int ipos = vi[k];
                int jpos = vj[k];
                if (inside_grid(ipos, jpos, gridsize)) {
                    Edge e(&vertices.at(i).at(j), &vertices.at(ipos).at(jpos), weights[ipos][jpos]);
                    G.add_edge(e);
                }
            }
        }
    }
    //print_graph(G);

    auto start = std::chrono::high_resolution_clock::now();

    list<Vertex> S = dijkstra(G, vertices.at(0).at(0), vertices.at(gridsize-1).at(gridsize-1), gridsize);

    Vertex dest;
    for (Vertex v : S) {
        if (v == Vertex(gridsize-1, gridsize-1)) {
            dest = v;
            break;
        }
    }

    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();

    cout << dest.d << '\n';
    cout << "Execution time: " << microseconds << '\n';
}