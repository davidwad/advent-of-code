#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctype.h>
#include <cstring>
#include <chrono>
using namespace std;


void parse_input(int* fish, string line) {
    char c;
    int k = 0;
    for (int i = 0; i < line.length(); i++) {
        c = line[i];
        if (isdigit(c)) {
            *(fish + k) = c - '0';
            k++;
        }
    }
}

unsigned long int growth(unsigned long int** cache, int timer, int days) {
    unsigned long int value = cache[timer][days];
    if (value != 0) {
        return value;
    } else if (days == 0) {
        value = 1;
        cache[timer][days] = value;
        return value;
    } else if (timer == 0) {
        value = growth(cache, 6, days - 1) + growth(cache, 8, days - 1);
        cache[timer][days] = value;
        return value;
    } else {
        value = growth(cache, timer - 1, days - 1);
        cache[timer][days] = value;
        return value;
    }
}

void init_cache(unsigned long int** cache, int maxtimer, int totaldays) {
    for (int timer = 0; timer < maxtimer; timer++) {
        for (int days = 0; days < totaldays; days++) {
            cache[timer][days] = 0;
        }
    }
}

void print_cache(unsigned long int** cache, int maxtimer, int totaldays) {
    for (int timer = 0; timer < maxtimer; timer++) {
        for (int days = 0; days < totaldays; days++) {
            cout << cache[timer][days] << ' ';
        }
    cout << '\n';
    }
}

int main() {
    const int inputlen = 300;
    const int totaldays = 256;
    const int maxtimer = 8;
    ifstream input("input.txt");
    string line;
    int* fish = new int[inputlen];

    getline(input, line);
    parse_input(fish, line);

    auto start = std::chrono::high_resolution_clock::now();

    unsigned long int** cache = new unsigned long int*[maxtimer+1];
    for (int i = 0; i < maxtimer+1; i++) {
        cache[i] = new unsigned long int[totaldays+1];
    }
    init_cache(cache, maxtimer+1, totaldays+1);

    unsigned long int sum = 0;
    for (int i = 0; i < inputlen; i++) {
        sum += growth(cache, fish[i], totaldays);
    }
    //print_cache(cache, maxtimer+1, totaldays+1);
    cout << '\n' << sum << '\n';
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    cout << "Execution time: " << microseconds << '\n';
}