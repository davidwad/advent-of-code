
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <queue>
#include <vector>
#include <chrono>
#include "graph.h"
using namespace std;


bool inside_grid(int i, int j, int gridsize) {
    return i >= 0 && j >= 0 && i < gridsize && j < gridsize;
}

bool exists(Vertex vertex, list<Vertex> vertices) {
    for (Vertex v : vertices) {
        if (v == vertex) { return true; }
    }
    return false;
}

void print_vertex(Vertex v) {
    cout << v.iloc << ',' << v.jloc << ',' << v.d << '\n';
}

class VertexCmp {
    public:
        bool operator() (const Vertex v1, const Vertex v2) const {
            return (v1.d > v2.d);
        }
};
int main() {
    const int gridsize = 10;

    ifstream input("exampleinput.txt");
    string line;
    int weights[gridsize][gridsize];
    vector<vector<Vertex>> vertices;
    Graph G;
    list<Vertex> V;
    list<Vertex> S;
    priority_queue<Vertex,vector<Vertex>,VertexCmp> Q;

    for (int i=0; i<gridsize; i++) {
        getline(input, line);
        vector<Vertex> vrow;
        for (int j=0; j<gridsize; j++) {
            weights[i][j] = line[j] - '0';
            Vertex v(i, j);
            // cout << v.iloc << ',' << v.jloc << '\n';
            G.add_vertex(v);
            vrow.push_back(v);
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

    // for (Edge e : G.neighb_edges(vertices.at(9).at(9))) {
    //     cout << "ipos: " << e.end->iloc << " | jpos: " << e.end->jloc << " | weight: " << e.weight << '\n';
    // }

    auto start = std::chrono::high_resolution_clock::now();

    int d = 0;
    // Needs to be pointer?
    Vertex s = vertices.at(0).at(0);
    s.d = 0;
    G.vertices.remove(s);
    vertices.at(0).at(1).d = weights[0][1];
    vertices.at(1).at(0).d = weights[1][0];
    for (Vertex v : G.vertices) {
        if (v == Vertex(0, 1)) {
            v.d = weights[0][1];
            //S.push_back(v);
        }
        if (v == Vertex(1, 0)) {
            v.d = weights[1][0];
            //S.push_back(v);
        }
        Q.push(v);
        //print_vertex(Q.top());
    }
    for (Vertex v : G.vertices) {
        V.push_back(v);
    }
    S.push_back(s);
    //print_vertex(*S.back());

    int n = 0;
    while (!V.empty()) {
        // for (Node u : S) {
        //     int du = u.d;
        //     list<Edge> edges = G.get_edges(u);
        //     for (Edge e : G.get_edges(u);) {
        //         Node v = e.end;
        //         int w = v.weight;
        //         if (!exists(v, S)) {
        //             v.d = du + w;
        //         }
        //     }
        // }
        // priority_queue<Vertex,vector<Vertex>,VertexCmp> Q;
        // Vertex u = S.back();
        // print_vertex(u);
        //cout << u->iloc << ',' << u->jloc << '\n';
        // int du = u->d;
        // list<Edge> edges = G.neighb_edges(u);
        int dmin = INT32_MAX;
        Vertex umin;
        Vertex vmin;

        Vertex u = Q.top();
        //Q.pop();
        // if (!exists(u, S)) {
        //     continue;
        // }
        cout << "u: ";
        print_vertex(u);
        //if (!exists(u, S)) { break; }
        
        for (Edge e : G.neighb_edges(u)) {
            Vertex v = *e.end;
            //v->pred = &u;
            int w = e.weight;
            if (!exists(v, S)) {
                v.d = u.d + w;
                Q.push(v);
                // if (u.d + w < v.d) {
                //     v.d = u.d + w;
                //     Q.push(v);
                //     // cout << "\tv: ";
                //     // print_vertex(v);
                // }
                
                // if (u.d + w < dmin) {
                //     dmin = u.d + w;
                //     umin = u;
                //     vmin = v;
                // }
                // cout << "\tv: ";
                // print_vertex(*v);
            }
        }
        // for (Vertex u : S) {
        //     // cout << "u: ";
        //     // print_vertex(u);
        //     for (Edge e : G.neighb_edges(u)) {
        //         Vertex* v = e.end;
        //         //v->pred = &u;
        //         int w = e.weight;
        //         if (!exists(*v, S)) {
        //             if (u.d + w < dmin) {
        //                 //v->pred = &u;
        //                 dmin = u.d + w;
        //                 umin = u;
        //                 //*vmin.pred = u;
        //                 vmin = *v;
        //             }
        //             // cout << "\tv: ";
        //             // print_vertex(*v);
        //         }
        //     }
        // }
        //break;
        // vmin.d = dmin;
        // vmin.pred = &umin;
        Vertex v = Q.top();
        Q.pop();
        V.remove(v);
        S.push_back(v);
        // if (v == Vertex(gridsize-1,gridsize-1)) {
        //     break;
        // }
        // if (Q.empty()) {
        //     cout << "Q empty" << '\n'; 

        // } else {
        //     Vertex v = Q.top();
        //     //print_vertex(v);
        //     //cout << vp->d << '\n';
        //     V.remove(v);
        //     S.push_back(v);
        //     // cout << V.size() << '\n';
        //     // cout << S.size() << '\n';
        // }
        cout << n << '\n';
        n++;
    }

    Vertex dest;
    for (Vertex v : S) {
        if (v == Vertex(gridsize-1,gridsize-1)) {
            dest = v;
        }
    }

    // for (Edge e : G.neighb_edges(vertices.at(9).at(9))) {
    //     print_vertex(*e.end);
    // }
    //print_vertex(vertices.at(9).at(8));

    // Vertex v = dest;
    // int sum = 0;
    // int i = 0;
    // while (v.pred != nullptr) {
    //     print_vertex(v);
    //     v = *v.pred;
    //     if (i > 2) { break; }
    //     i++;
    // }

    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();

    cout << dest.d << '\n';
    cout << "Execution time: " << microseconds << '\n';
}