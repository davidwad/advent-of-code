#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    ifstream input ("input.txt");
    string line;
    int value;
    int aim = 0;
    int depth = 0;
    int horizontal = 0;
    while (getline(input, line)) {
        if (input.peek() != EOF) {
            line.pop_back();
        }
        value = line.back() - '0';
        line.pop_back();
        line.pop_back();

        if (line == "forward") {
            horizontal += value;
            depth += aim * value;
        } else if (line == "up") {
            aim -= value;
        } else if (line == "down") {
            aim += value;
        }
    }
    cout << to_string(horizontal * depth) << '\n';
}
