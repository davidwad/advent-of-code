
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <queue>
#include <vector>
#include <chrono>
using namespace std;


class Node {
    public:
        int ipos;
        int jpos;
        int d = INT32_MAX;
        Node* pred;

        Node () {

        }

        Node(int i, int j) {
            ipos = i;
            jpos = j;
        }
        bool operator==(const Node& node) {
            return node.ipos == ipos && node.jpos == jpos;
        }
};

class Edge {
    public:
        Node start;
        Node end;
        int weight;

        Edge(Node s, Node e, int w) {
            start = s;
            end = e;
            weight = w;
        }
};

class Graph {
    public:
        list<Edge> adj_list;

        void add_edge(Edge e) {
            adj_list.push_back(e);
        }

        list<Edge> get_edges(Node node) {
            list<Edge> edges;
            for (Edge e : adj_list) {
                //if (e.start.equals(node)) {
                if (e.start == node) {
                    edges.push_back(e);
                }
            }
            return edges;
        }

        // list<Node> get_neighbours(Node node) {
        //     list
        // }
};

bool inside_grid(int i, int j, int gridsize) {
    return i >= 0 && j >= 0 && i < gridsize && j < gridsize;
}

bool exists(Node node, list<Node> nodes) {
    for (Node n : nodes) {
        if (n == node) { return true; }
    }
    return false;
}

bool compare_dist(Node a, Node b) {
    return a.d < b.d;
}
class NodeComparison {
    public:
        bool operator() (const Node& a, const Node& b) const {
            return (a.d<b.d);
        }
};
int main() {
    const int gridsize = 10;

    ifstream input("exampleinput.txt");
    string line;
    int weights[gridsize][gridsize];
    Graph G;
    list<Node> V;
    list<Node> S;
    priority_queue<Node,vector<Node>,NodeComparison> Q;

    for (int i=0; i<gridsize; i++) {
        getline(input, line);
        for (int  j=0; j<gridsize; j++) {
            weights[i][j] = line[j] - '0';
        }
    }

    for (int i=0; i<gridsize; i++) {
        for (int j=0; j<gridsize; j++) {
            Node node(i, j);
            V.push_back(node);
            int vi[4] = {i-1, i, i, i+1};
            int vj[4] = {j, j-1, j+1, j};
            for (int k=0; k<4; k++) {
                int ipos = vi[k];
                int jpos = vj[k];
                if (inside_grid(ipos, jpos, gridsize)) {
                    Edge e(node, Node(ipos, jpos), weights[ipos][jpos]);
                    G.add_edge(e);
                }
            }
        }
    }

    // for (Edge e : V.get_edges(Node(1,1))) {
    //     cout << "ipos: " << e.end.ipos << " | jpos: " << e.end.jpos << " | weight: " << e.weight << '\n';
    // }

    auto start = std::chrono::high_resolution_clock::now();

    int d = 0;

    Node s = Node(0,0);
    s.d = 0;
    V.remove(s);
    for (Node node : V) {
        Q.push(node);
    }
    S.push_back(s);

    while (!Q.empty()) {
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
        Node u = S.back();
        int du = u.d;
        list<Edge> edges = G.get_edges(u);
        for (Edge e : G.get_edges(u)) {
            Node v = e.end;
            int w = e.weight;
            if (!exists(v, S)) {
                v.d = du + w;
            }
        }
        Node v = Q.top();
        Q.pop();
        S.push_back(v);
    }

    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();

    //cout << counts[maxidx] - counts[minidx] << '\n';
    cout << "Execution time: " << microseconds << '\n';
}