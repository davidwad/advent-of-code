#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    string lastDepth;
    string currDepth;
    int increases;
    ifstream inp ("input.txt");
    int i = 0;
    getline(inp, lastDepth);
    while ( getline(inp, currDepth) ) {
        if (stoi(currDepth, nullptr) > stoi(lastDepth, nullptr)) {
            increases++;
        }
        lastDepth = currDepth;
    }
    string str = to_string(increases);
    cout << str << '\n';

}