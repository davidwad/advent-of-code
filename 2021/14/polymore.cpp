#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include <chrono>
using namespace std;


class CharCount {
    public:
        long long int counts[26] = {};

        void increase(char c) {
            counts[c-'A']++;
        }
        long long int get(int i) {
            return counts[i];
        }
        void add(CharCount count_to_add) {
            for (int i = 0; i < 26; i++) {
                counts[i] += count_to_add.counts[i];
            }
        }
};

CharCount fill(char left, char right, int step, map<string, char> rules, map<string, CharCount>* cache) {
    CharCount count;
    if (step == 0) {
        return count;
    }

    string key = {left, right, (char)(step+'A')};
    if (cache->count(key) > 0) {
        //cout << "Accessed cache" << '\n';
        return cache->at(key);
    }

    char mid = rules[{left, right}];
    count.increase(mid);
    count.add(fill(left, mid, step-1, rules, cache));
    count.add(fill(mid, right, step-1, rules, cache));
    key = {left, right, (char)(step+'A')};
    cache->insert(pair<string,CharCount>(key, count));
    return count;
}

void print_elements(list<char> elements) {
    for (char c : elements) {
        cout << c;
    }
    cout << '\n';
}

int main() {
    const int steps = 40;

    ifstream input("input.txt");
    string line;
    map<string, char> rules;
    map<string, CharCount> cache;
    CharCount count;
    list<char> elements;

    getline(input, line);
    for (char c : line) {
        elements.push_back(c);
        count.increase(c);
    }

    getline(input, line);
    while (getline(input, line)) {
        string key = line.substr(0, 2);
        char value = line[6];
        rules.insert(pair<string,char>(key, value));
    }
    
    auto start = std::chrono::high_resolution_clock::now();
    for (auto it=elements.begin(); it != elements.end(); ++it) {
        char c1 = *it;
        ++it;
        if (it == elements.end()) { break; }
        char c2 = *it;
        --it;
        count.add(fill(c1, c2, steps, rules, &cache));
    }

    int maxidx = 0;
    for (int i = 0; i < 26; i++) {
        if (count.get(i) > count.get(maxidx)) { maxidx = i; }
    }
    int minidx = maxidx;
    for (int i = 0; i < 26; i++) {
        if (count.get(i) > 0 && count.get(i) < count.get(minidx)) { minidx = i; }
    }

    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();

    cout << count.get(maxidx) - count.get(minidx) << '\n';
    cout << "Execution time: " << microseconds << '\n';
}