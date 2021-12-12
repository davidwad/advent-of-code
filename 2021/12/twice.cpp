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

bool has_visited(string cave, list<string> visited) {
    if (!string_upper(cave)) {
        for (string vcave : visited) {
            if (vcave == cave) {
                return false;
            }
        }
    }
    return true;
}

bool explorable(string cave, list<string> visited) {
    if (cave == "start") {
        return false;
    } else if (!string_upper(cave)) {
        int times_visited = 0;
        for (string vcave : visited) {
            if (vcave == cave) {
                return false;
            }
        }
    }
    return true;
}

bool use_pass(string cave, list<string> visited) {
    if (cave == "start" || cave == "end") {
        return false;
    } else if (!string_upper(cave)) {
        return true;
    }
    return false;
}

void explore(string cave, list<string> visited, bool pass, list<Edge> edges, list<list<string>>* paths) {
    visited.push_back(cave);
    if (cave == "end") {
        paths->push_back(visited);
    } else {
        for (Edge e : edges) {
            if (e.start == cave) {
                if (explorable(e.end, visited)) {
                    explore(e.end, visited, pass, edges, paths);
                }
                else if (pass && use_pass(e.end, visited)) {
                    explore(e.end, visited, false, edges, paths);
                }
            } else if (e.end == cave) {
                if (explorable(e.start, visited)) {
                    explore(e.start, visited, pass, edges, paths);
                }
                else if (pass && use_pass(e.start, visited)) {
                    explore(e.start, visited, false, edges, paths);
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

    explore("start", visited, true, edges, &paths);

    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();

    cout << paths.size() << '\n';
    cout << "Execution time: " << microseconds << '\n';
}