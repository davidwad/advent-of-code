#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <list>
#include <set>
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

void print_visited(list<string> visited) {
    for (string cave : visited) {
        cout << cave << '-';
    }
    cout << '\n';
}

void print_paths(list<list<string>> paths) {
    for (list<string> path : paths) {
        for (string cave : path) {
            cout << cave << '-';
        }
    cout << '\n';
    }
}

bool string_upper(string s) {
    for (char c : s) {
        if (islower(c)) {return false;}
    }
    return true;
}

bool explorable(string cave, list<string> visited) {
    if (cave == "start") {
        return false;
    } else if (!string_upper(cave)) {
        for (string vcave : visited) {
            if (vcave == cave) {return false;}
        }
    }
    return true;
}

void explore(string cave, list<string> visited, list<Edge> edges, list<list<string>>* paths) {
    visited.push_back(cave);
    if (cave == "end") {
        paths->push_back(visited);
    } else {
        for (Edge e : edges) {
            if (e.start == cave) {
                if (explorable(e.end, visited)) {
                    explore(e.end, visited, edges, paths);
                }
            } else if (e.end == cave) {
                if (explorable(e.start, visited)) {
                    explore(e.start, visited, edges, paths);
                }
            }
        }
    }
}

int main() {
    ifstream input("input.txt");
    string line;
    list<Edge> edges;
    list<string> visited;
    list<list<string>> paths;

    while(getline(input, line)) {
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
        edges.push_back(Edge(name1, name2));
    }

    auto start = std::chrono::high_resolution_clock::now();

    explore("start", visited, edges, &paths);

    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();

    cout << paths.size() << '\n';
    cout << "Execution time: " << microseconds << '\n';
}