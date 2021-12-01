#include <iostream>
#include <fstream>
#include <string>
#include <queue>
using namespace std;

int queuesum(queue<int> q, int skip) {
    int sum = 0;
    int depth;
    for (int i = 0; i < 4; i++) {
        depth = q.front();
        q.pop();
        if (i != skip) {
            sum += depth;
        }
    }
    return sum;
}

int main() {
    queue<int> depths;
    int increases = 0;
    string depth;
    int lastsum;
    int currsum;
    ifstream inp ("input.txt");
    int i = 0;
    while (getline(inp, depth)) {
        depths.push(stoi(depth, nullptr));
        if (i > 2) {
            currsum = queuesum(depths, 0);
            lastsum = queuesum(depths, 3);
            if(currsum > lastsum) {
                increases++;
            }
            depths.pop();
        }
        i++;
    }
    string result = to_string(increases);
    cout << result << '\n';
}
