
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <queue>
#include <vector>
#include <set>
#include <chrono>
#include "graph.h"
using namespace std;


// function dijkstra(G, S)
//     for each vertex V in G
//         dist[V] <- infinite
//         prev[V] <- NULL
//         If V != S, add V to Priority Queue Q
//     dist[S] <- 0
    
//     while Q IS NOT EMPTY
//         U <- Extract MIN from Q
//         for each unvisited neighbour V of U
//             temperoryDist <- dist[U] + edgeWeight(U, V)
//             if temperoryDist < dist[V]
//                 dist[V] <- temperoryDist
//                 prev[V] <- U
//     return dist[], prev[]

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
            return (v1.d < v2.d);
        }
};
int main() {
    const int gridsize = 10;

    ifstream input("exampleinput.txt");
    string line;
    int weights[gridsize][gridsize];
    vector<vector<Vertex>> vertices;
    Graph G;
    list<Vertex*> V;
    list<Vertex> S;
    //set<Vertex,VertexCmp> S;
    priority_queue<Vertex,vector<Vertex>,VertexCmp> Q;

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

    // for (Edge e : G.neighb_edges(vertices.at(9).at(9))) {
    //     cout << "ipos: " << e.end->iloc << " | jpos: " << e.end->jloc << " | weight: " << e.weight << '\n';
    // }

    auto start = std::chrono::high_resolution_clock::now();
    Vertex s = vertices.at(0).at(0);
    G.vertices.remove(s);
    for (Vertex v : G.vertices) {
        V.push_back(&v);
        Q.push(v);
    }
    s.d = 0;
    //cout << vertices.at(0).at(0).d << '\n';
    S.push_back(s);
    //print_vertex(*S.back());

    int n = 0;
    while (!V.empty()) {
        
        // for (Vertex u : S) {
        //     // cout << "u: ";
        //     // print_vertex(u);
        //     for (Edge e : G.neighb_edges(u)) {
        //         Vertex* vp = e.end;
        //         if (S.count(*vp) == 0) {
        //             if (u.d + e.weight < vp->d) {
        //                 vp->d = u.d + e.weight;
        //                 Q.push(*vp);
        //             }
        //             // cout << "\tv: ";
        //             // print_vertex(v);
        //         }
        //     }
        // }

        Vertex u = Q.top();
        cout << "u: ";
        print_vertex(u);
        for (Edge e : G.neighb_edges(u)) {
            Vertex* vp = e.end;
            if (!exists(*vp, S)) {
                if (u.d + e.weight < vp->d) {
                    vp->d = u.d + e.weight;
                    Q.push(*vp);
                }
                cout << "\tv: ";
                print_vertex(*vp);
            }
        }
        Vertex v = Q.top();
        Q.pop();
        cout << V.size() << '\n';
        V.remove(&v);
        cout << V.size() << '\n';
        S.push_back(v);
        //cout << n << '\n';
        n++;
    }

    // for (Edge e : G.neighb_edges(*vertices.at(9).at(9))) {
    //     print_vertex(*e.end);
    // }
    //print_vertex(vertices.at(9).at(8));

    // Vertex v = vertices.at(gridsize-1).at(gridsize-1);
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

    cout << vertices.at(gridsize-1).at(gridsize-1).d << '\n';
    cout << "Execution time: " << microseconds << '\n';
}