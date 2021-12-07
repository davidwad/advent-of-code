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

int average(vector<int> pos) {
    double quote;
    int sum = 0;
    int numcrabs = pos.size();
    for (int i = 0; i < numcrabs; i++) {
        sum += pos[i];
    }
    quote = (double)sum / (double)numcrabs;
    return floor(quote);
}

void init_cache(int* cache, int cachesize) {
    int sum = 0;
    for (int i = 0; i < cachesize; i++) {
        sum += i;
        cache[i] = sum;
    }
}

int calc_cost(int* cache, vector<int> pos, int avg) {
    int cost = 0;
    for (int p : pos) {
        cost += cache[abs(p - avg)];
    }
    return cost;
}


int main() {
    ifstream input("input.txt");
    string line;
    vector<int> pos;;
    int lcost;
    int hcost;
    int cost;
    int avg;
    int cachesize;
    int* cache;

    getline(input, line);
    pos = parse_positions(line);

    auto start = std::chrono::high_resolution_clock::now();

    sort(pos.begin(), pos.end());
    avg = average(pos);

    cachesize = max(pos.back() - avg, pos.front() - avg) + 1;
    cache = new int[cachesize];
    init_cache(cache, cachesize);

    lcost = calc_cost(cache, pos, avg);
    hcost = calc_cost(cache, pos, avg + 1);
    cost = min(lcost, hcost);

    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    cout << cost << '\n';
    cout << "Execution time: " << microseconds << '\n';
}