#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
using namespace std;

bool valid(int h, int w, int mapheight, int mapwidth) {
    if (h < 0 || w < 0 || h >= mapheight || w >= mapwidth) {
        return false;
    } else {
        return true;
    }
}

bool lowest(int** hmap, int h, int w, int mapheight, int mapwidth) {
    int orglow = hmap[h][w];

    for (int i = h - 1; i <= h + 1; i++) {
        for (int j = w - 1; j <= w + 1; j++) {
            if (abs(i - h) + abs(j - w) < 2) {
                if (!(i == h && j == w)) {
                    if (valid(i, j, mapheight, mapwidth)) {
                        if (hmap[i][j] <= orglow) {
                            return false;
                        }
                    }
                }
            }
        }  
    }
    return true;
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
    int risk = 0;
    int** hmap = new int*[mapheight];
    for (int i = 0; i < mapheight; i++) {
        hmap[i] = new int[mapwidth];
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
    print_map(hmap, mapheight, mapwidth);

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < mapheight; i++) {
        for (int j = 0; j < mapwidth; j++) {
            if (lowest(hmap, i, j, mapheight, mapwidth)) {
                risk += hmap[i][j] + 1;
            }
        }
    }

    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    cout << risk << '\n';
    cout << "Execution time: " << microseconds << '\n';
}