#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <list>
#include <chrono>
using namespace std;

class Edge {
    public:
        string start;
        string end;

        Edge(string s, string e) {
            start = s;
            end = e;
        }
};

class Node {
    public:
        string name;
        list<Node*> neighbours;
        Node(string name_) {
            name = name_;
        }
};

bool node_exists(string name, list<Node> nodes) {
    if (!nodes.empty()) {
        for (Node node : nodes) {
            if (node.name == name) {
                return true;
            }
        }
    }
    return false;
}

// void add_neighbour(string name, Node* neighbour, list<Node>* nodes) {
//     for (Node node : *nodes) {
//         if (node.name == name) {
//             node.neighbours.push_back(neighbour);
//         }
//     }
// }

// Node* get_node(string name, list<Node*>* nodes) {
//     if (!nodes->empty()) {
//         for (Node* node : *nodes) {
//             // cout << node->name << '\n';
//             // cout << '-' << '\n';
//             if (node->name == name) {
//                 return node;
//             }
//         }
//     }
//     return nullptr;
// }

bool explorable(string cave, list<string> visited) {
    if (cave == "start") {
        return false;
    } else if (!string_upper(cave)) {
        for (string vcave : visited) {
            if (vcace == cave) {return false;}
        }
    }
}

bool string_upper(string s) {
    for (char c : s) {
        if (islower(c)) {return false;}
    }
    return true;
}

void explore(string cave, list<string> visited, list<Edge> edges, list<list<string>>* paths) {
    visited.push_back(cave);
    for (Edge e : edges) {
        if (e.start == cave) {
            if (e.end == "end") {
                *paths.push_back(visited);
                //return;
            } else if (explorable(e.end, visited)) {
                explore(e.end, visited, edges, paths);
            }
        }
    }
}

void print_neighbours(Node node) {
    for (Node* neighb : node.neighbours) {
        cout << neighb->name << '-';
    }
    cout << '\n';
}

void print_paths(list<list<string>> paths) {
    for (list<string> path : paths) {
        for (string cave : path) {
            cout << cave, << '-';
        }
    cout << '\n';
    }
}

int main() {
    /* IDEA 1:
        Start in start:
            For each neighbour:
                If neighbour is end:
                    Add visited to paths
                    Return
                If not (neighbour small and visited):
                    Add current cave to visited
                    Visit neighbours

    */
    // Make list of all names, and list of all edges.
    // For each name:
    //    For each edge:
    //      If name == edge.start:
    //          neighbours.add(edge.end)


    ifstream input("exampleinput.txt");
    string line;
    list<Node> nodes;
    list<Edge> edges;

    while(getline(input, line)) {
        // Node node1;
        // Node node2;
        string name1;
        string name2;
        string substr = "";
        int i = 0; 
        char c = line[i]; 
        while (i < line.length()) {
            c = line[i];
            
            if (isalpha(c)) {
                substr.push_back(c);
            } else {
                name1 = substr;
                substr = "";
            }
            i++;
        }
        name2 = substr;
        if (node_exists(name1, nodes)) {
            // for (Node node : nodes) {
            //     if (node.name == name1) {
            //         node1 = node;
            //     }
            // }
        } else {
            Node node1 = Node(name1);
            nodes.push_back(node1);
        }
        if (node_exists(name2, nodes)) {
            // for (Node node : nodes) {
            //     if (node.name == name2) {
            //         node2 = node;
            //     }
            // }       
        } else {
            Node node2 = Node(name2);
            nodes.push_back(node2);
        }
        edges.push_back(Edge(name1, name2));
        // add_neighbour(name1, &node2, &nodes);
        // add_neighbour(name2, &node1, &nodes);

        //     if (node_exists(name1, nodes)) {
        //         cout << "Exists" << '\n';
        //         cout << '-' << '\n';
        //         node1 = get_node(name1, &nodes);
        //         cout << '-' << '\n';
        //     } else {
        //         //Node n1(name1);
        //         cout << '-' << '\n';
        //         *node1 = Node(name1);
        //         cout << '-' << '\n';
        //         nodes.push_back(node1);
        //         cout << '-' << '\n';
        //     }
        //     if (node_exists(name2, nodes)) {
        //         cout << "Exists" << '\n';
        //         node2 = get_node(name2, &nodes);
        //     } else {
        //         Node n2(name2);
        //         node2 = &n2;
        //         nodes.push_back(node2);
        //     }
        //     node1->neighbours.push_back(node2);
        //     node2->neighbours.push_back(node1);
        //     cout << name1 << '-' << name2 << '\n';
        //     cout << nodes.front()->name << '\n';
    }
    for (Node n1 : nodes) {
        for (Node n2: nodes) {
            for (Edge e : edges) {
                if (n1.name == e.start && n2.name == e.end) {
                    n1.neighbours.push_back(&n2);
                }
            }
        }
    }

    cout << nodes.size() << '\n';
    for (Node n : nodes) {
        cout << n.name << ": ";
        print_neighbours(n);
    }
    


    auto start = std::chrono::high_resolution_clock::now();

    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    //cout << res << '\n';
    cout << "Execution time: " << microseconds << '\n';
}