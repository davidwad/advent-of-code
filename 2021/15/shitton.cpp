
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


class VertexCmp {
    public:
        bool operator() (const Vertex v1, const Vertex v2) const {
            return (v1.d > v2.d);
        }
};

class VertexMapCmp {
    public:
        bool operator() (const Vertex& v1, const Vertex& v2) const {
            return (v1.d > v2.d);
        }
};

bool mapcomp (const Vertex v1, const Vertex v2) {
    return (v1.d > v2.d);
}

bool inside_grid(int i, int j, int gridsize) {
    return i >= 0 && j >= 0 && i < gridsize && j < gridsize;
}

bool exists(Vertex vertex, list<Vertex> vertices) {
    for (Vertex v : vertices) {
        if (v == vertex) { return true; }
    }
    return false;
}

// bool valid(Vertex v, map<Vertex,int,bool(*)(Vertex,Vertex)> min) {
//     int minval = min[v];
//     if (minval < v.d) { return false; }
//     return true;
// }

// void update_min(Vertex v, map<Vertex,int,bool(*)(Vertex,Vertex)>* min) {
//     auto p = min->insert(pair<Vertex,int>(v, v.d));
//     if (!p.second) {
//         //*p.first = pair<Vertex,int>(v,v.d);
//         p.first->second = v.d;
//     }
// }

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



set<Vertex> dijkstra(Graph G, Vertex s, Vertex t) {
    set<Vertex> S;
    priority_queue<Vertex,vector<Vertex>,VertexCmp> Q;
    bool(*fn_pt)(Vertex,Vertex) = mapcomp;
    map<Vertex,int,bool(*)(Vertex,Vertex)> min (fn_pt);

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
        if (u == t) { break; }
        Q.pop();
        while (!valid(u, min) && !Q.empty()) {
            u = Q.top();
            Q.pop();
        }
        S.insert(u);
        for (Edge e : G.neighb_edges(u)) {
            Vertex* v = e.end;
            int w = e.weight;
            if (S.find(*v) != S.end()) {
                if (u.d + w < v->d) {
                    v->d = u.d + w;
                    v->pred = &u;
                    Q.push(*v);
                    update_min(*v, &min);
                    // auto p = min->insert(pair<Vertex,int>(v, v.d));
                    // if (!p.second) {
                    //     //*p.first = pair<Vertex,int>(v,v.d);
                    //     p.first->second = v.d;
                    // }
                }
            }

        }
        n++;
    }
    return S;
}


int main() {
    const int gridsize = 100;

    ifstream input("input.txt");
    string line;
    int weights[gridsize][gridsize];
    vector<vector<Vertex>> vertices;
    Graph G;

    for (int i=0; i<gridsize; i++) {
        getline(input, line);
        vector<Vertex> vrow;
        for (int j=0; j<gridsize; j++) {
            weights[i][j] = line[j] - '0';
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

    set<Vertex> S = dijkstra(G, vertices.at(0).at(0), vertices.at(gridsize-1).at(gridsize-1));

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