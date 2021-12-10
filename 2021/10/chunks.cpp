#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <chrono>
using namespace std;


bool compare_chunk(char c1, char c2) {
    if (c1 == '(' and c2 == ')') {return true;}
    if (c1 == '[' and c2 == ']') {return true;}
    if (c1 == '{' and c2 == '}') {return true;}
    if (c1 == '<' and c2 == '>') {return true;}
    return false;
}

int chunk_score(char c) {
    switch (c) {
        case ')': return 3;
        case ']': return 57;
        case '}': return 1197;
        case '>': return 25137;
        default: return 0;
    }
}

int line_score(string line) {
    stack<char> chunkstack;
    char stackchar;
    long int score = 0;
    for (char c : line) {
        switch (c) {
            case '(':
            case '[':
            case '{':
            case '<':
                chunkstack.push(c);
                break;

            case ')':
            case ']':
            case '}':
            case '>':
                stackchar = chunkstack.top();
                chunkstack.pop();
                if (!compare_chunk(stackchar, c)) {
                    return chunk_score(c);
                }
                break;
        }
    }
    return 0;

}

int main() {
    ifstream input("input.txt");
    string line;
    long int score = 0;

    auto start = std::chrono::high_resolution_clock::now();
    while (getline(input, line)) {
        score += line_score(line);
    }


    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    cout << score << '\n';
    cout << "Execution time: " << microseconds << '\n';
}