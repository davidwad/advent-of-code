#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <chrono>
using namespace std;


vector<int> parse_positions(string line) {
    vector<int> pos;
    char c;
    string numstr = "";
    int i = 0;  
    while (i < line.length()) {
        c = line[i];
        
        if (isdigit(c)) {
            numstr.push_back(c);
        } else {
            if (!numstr.empty()) {
                pos.push_back(stoi(numstr, nullptr));
                numstr = "";
            }
        }
        i++;
    }
    pos.push_back(stoi(numstr, nullptr));
    return pos;
}

void print_positions(vector<int> pos) {

    for (int i = 0; i < pos.size(); i++) {
        cout << pos.at(i) << ' ';
    }
    cout << '\n';
}

int calc_cost(vector<int> pos) {
    int cost = 0;
    int size = pos.size();
    int middle = pos.at(size/2);
    for (int p : pos) {
        cost += abs(p - middle);
    }
    return cost;
}

int main() {
    ifstream input("input.txt");
    string line;
    vector<int> pos;;
    int cost;

    getline(input, line);
    pos = parse_positions(line);

    auto start = std::chrono::high_resolution_clock::now();

    sort(pos.begin(), pos.end());
    cost = calc_cost(pos);
    cout << cost << '\n';

    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    cout << "Execution time: " << microseconds << '\n';
}