#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <chrono>
using namespace std;


class Point {
    public:
        int h;
        int w;

        Point(int starth, int startw) {
            h = starth;
            w = startw;
        }
};

bool valid(int h, int w, int mapheight, int mapwidth) {
    if (h < 0 || w < 0 || h >= mapheight || w >= mapwidth) {
        return false;
    } else {
        return true;
    }
}

void go_down(int** hmap, Point* p, int mapheight, int mapwidth) {
    int currheight = hmap[p->h][p->w];
    for (int i = (p->h) - 1; i <= (p->h) + 1; i++) {
        for (int j = (p->w) - 1; j <= (p->w) + 1; j++) {
            if (abs(i - p->h) + abs(j - p->w) < 2) {
                if (!(i == p->h && j == p->w)) {
                    if (valid(i, j, mapheight, mapwidth)) {
                        if (hmap[i][j] < currheight) {
                            p->h = i;
                            p->w = j;
                            go_down(hmap, p, mapheight, mapwidth);
                        }
                    }
                }
            }
        }  
    }
}

void print_map(int** hmap, int mapheight, int mapwidth) {
    for (int i = 0; i < mapheight; i++) {
        for (int j = 0; j < mapwidth; j++) {
            cout << hmap[i][j];
        }
        cout << '\n';
    }
    cout << '\n';
}

int main() {
    const int mapheight = 100;
    const int mapwidth = 100;

    ifstream input("input.txt");
    string line;
    int** hmap = new int*[mapheight];
    int** lowpoints = new int*[mapheight];
    priority_queue<int> q;
    for (int i = 0; i < mapheight; i++) {
        hmap[i] = new int[mapwidth];
        lowpoints[i] = new int[mapwidth];
    }
    int i = 0;
    while (getline(input, line)) {
        int j = 0;
        for (char height : line) {
            if (isdigit(height)) {
                hmap[i][j] = height - '0';
                j++;
            }
        }
        i++;
    }

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < mapheight; i++) {
        for (int j = 0; j < mapwidth; j++) {
            if (hmap[i][j] != 9) {
                Point p(i, j);
                go_down(hmap, &p, mapheight, mapwidth);
                int idx = mapwidth * j + i;
                lowpoints[p.h][p.w] += 1;
            }
        }
    }
    for (int i = 0; i < mapheight; i++) {
        for (int j = 0; j < mapwidth; j++) {
            int npoints = lowpoints[i][j];
            if (npoints != 0) {
                q.push(npoints);
            }
        }
    }
    int res = 1;
    for (int i = 0; i < 3; i++) {
        res *= q.top();
        q.pop();
    }

    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    cout << res << '\n';
    cout << "Execution time: " << microseconds << '\n';
}