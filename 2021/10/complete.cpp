#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <list>
#include <chrono>
using namespace std;


bool compare_chunk(char c1, char c2) {
    if (c1 == '(' and c2 == ')') {return true;}
    if (c1 == '[' and c2 == ']') {return true;}
    if (c1 == '{' and c2 == '}') {return true;}
    if (c1 == '<' and c2 == '>') {return true;}
    return false;
}

long long int chunk_score(string completion) {
    long long int score = 0;
    for (char c : completion) {
        score *= 5;
        switch(c) {
            case ')':
                score += 1;
                break;
            case ']':
                score += 2;
                break;
            case '}':
                score += 3;
                break;
            case '>':
                score += 4;
                break;
            default: score += 0;
        }
    }
    return score;
}

char chunk_pair(char c) {
    switch (c) {
        case '(': return ')';
        case '[': return ']';
        case '{': return '}';
        case '<': return '>';
        // case ')': return '(';
        // case ']': return '[';
        // case '}': return '{';
        // case '>': return '<';
        default: return 0;
    }
}

bool line_corrupt(string line) {
    stack<char> chunkstack;
    char stackchar;
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
                    return true;
                }
                break;
        }
    }
    return false;

}

string complete_line(string line) {
    string completion;
    stack<char> chunkstack;
    char stackchar;
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
                break;
        }
    }
    while (!chunkstack.empty()) {
        completion.push_back(chunk_pair(chunkstack.top()));
        chunkstack.pop();
    }
    return completion;
}

int main() {
    ifstream input("input.txt");
    string line;

    list<long long int> scores;
    long long int finalscore;

    auto start = std::chrono::high_resolution_clock::now();
    while (getline(input, line)) {
        if (!line_corrupt(line)) {
            scores.push_back(chunk_score(complete_line(line)));
        }
    }
    scores.sort();
    int i = 0;
    for (long long int score : scores) {
        if (i == scores.size() / 2) {
            finalscore = score;
            break;
        }
        i++;
    }


    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    cout << finalscore << '\n';
    cout << "Execution time: " << microseconds << '\n';
}