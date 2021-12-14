
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include <chrono>
using namespace std;


void print_elements(list<char> elements) {
    for (char c : elements) {
        cout << c;
    }
    cout << '\n';
}

void print_counts(int counts[26]) {
    // for (pair<char, int*> p : counts) {
    //     cout << p.first << ": " << *p.second << '\n';
    // }
    for (int i = 0; i < 26; i++) {
        cout << (char)('A'+i) << ": " << counts[i] << '\n';
    }
}

int main() {
    const int steps = 10;

    ifstream input("input.txt");
    string line;
    map<string, char> rules;
    int counts[26] = {0};
    list<char> elements;

    getline(input, line);
    for (char c : line) {
        elements.push_back(c);
        counts[c-'A']++;
    }

    getline(input, line);
    while (getline(input, line)) {
        string key = line.substr(0, 2);
        char value = line[6];
        rules.insert(pair<string,char>(key, value));
    }
    
    auto start = std::chrono::high_resolution_clock::now();

    char c1;
    char c2;
    char ins;
    map<char,int>::iterator cit;
    for (int step=0; step < steps; step++) {
        cout << step << '\n';
        for (auto it=elements.begin(); it != elements.end(); ++it) {
            c1 = *it;
            ++it;
            if (it == elements.end()) { break; }
            c2 = *it;
            string key({c1, c2});
            ins = rules[key];
            elements.insert(it, ins);
            counts[ins-'A']++;
            --it;
        }
    }

    int maxidx = 0;
    for (int i = 0; i < 26; i++) {
        if (counts[i] > counts[maxidx]) { maxidx = i; }
    }
    int minidx = maxidx;
    for (int i = 0; i < 26; i++) {
        if (counts[i] > 0 && counts[i] < counts[minidx]) { minidx = i; }
    }

    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();

    cout << counts[maxidx] - counts[minidx] << '\n';
    cout << "Execution time: " << microseconds << '\n';
}