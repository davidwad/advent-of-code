#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctype.h>
#include <cstring>
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

int growth(int timer, int days) {
    if (days == 0) {
        return 1;
    } else if (timer == 0) {
        return growth(6, days - 1) + growth(8, days - 1);
    } else {
        return growth(timer - 1, days - 1);
    }
}

int main() {
    const int inputlen = 300;
    const int days = 80;
    ifstream input("input.txt");
    string line;
    int* fish = new int[inputlen];

    getline(input, line);
    parse_input(fish, line);

    int sum = 0;
    for (int i = 0; i < inputlen; i++) {
        sum += growth(fish[i], days);
    }
    cout << sum << '\n';
}