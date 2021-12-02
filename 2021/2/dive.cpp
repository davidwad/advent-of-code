#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    ifstream input ("input.txt");
    string line;
    char value;
    int depth = 0;
    int horizontal = 0;
    while (getline(input, line)) {
        if (input.peek() != EOF) {
            line.pop_back();
        }
        value = line.back();
        line.pop_back();
        line.pop_back();
        if (line == "forward") {
            horizontal += value - '0';
        } else if (line == "up") {
            depth -= value - '0';
        } else if (line == "down") {
            depth += value - '0';
        }
    }
    cout << to_string(horizontal * depth) << '\n';
}
