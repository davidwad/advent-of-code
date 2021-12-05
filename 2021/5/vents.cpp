#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctype.h>
#include <cstring>
using namespace std;


int** parse_coords(string line) {
    int* coords = new int[4];
    char c;
    string numstr = "";
    int i = 0;
    int k = 0;
    while (i < line.length()) {
        c = line[i];
        
        if (isdigit(c)) {
            numstr.push_back(c);
        } else {
            if (!numstr.empty()) {
                
                coords[k] = stoi(numstr, nullptr);
                numstr = "";
                k++;
            }
        }
        i++;
    }
    int** ret = &coords;
    return ret;
}


void bresenhams(int** grid, int x0, int y0, int x1, int y1) {
    int dx = abs(x1 - x0);
    int sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0);
    int sy = y0<y1 ? 1 : -1;
    int err = dx+dy; 
    while (true) {
        grid[x0][y0] += 1;
        if (x0 == x1 && y0 == y1) {
            return;
        }
        int e2 = 2*err;
        if (e2 >= dy) {
                        err += dy;
            x0 += sx;
        } 
        if (e2 <= dx) {
            err += dx;
            y0 += sy;
        }
    }
}

int danger(int** grid, int gridsize) {
    int sum = 0;
    for (int i = 0; i < gridsize; i++) {
        for (int j= 0; j < gridsize; j++) {
            if (grid[i][j] > 1) {
                sum++;
            }
        }
    }
    return sum;
}

void print_grid(int** grid, int gridsize) {
    for (int i = 0; i < gridsize; i++) {
        for (int j= 0; j < gridsize; j++) {
            cout << grid[i][j];
        }
        cout << '\n';
    }
}

void print_coords(int* coords) {
    for (int i = 0; i < 4; i++) {
        cout << coords[i] << ' ';
    }
    cout << '\n';
}


int main() {
    const int gridsize = 1000;
    ifstream input("input.txt");
    string line;
    int* coords;

    int** grid = new int*[gridsize];
    for (int i = 0; i < gridsize; i++) {
        grid[i] = new int[gridsize];
    }

    while (getline(input, line)) {
        coords = *parse_coords(line);
        if (coords[0] == coords[2] || coords[1] == coords[3]) {
            bresenhams(grid, coords[0], coords[1], coords[2], coords[3]);
        }
    }

    cout << danger(grid, gridsize) << '\n';
}