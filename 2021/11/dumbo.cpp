
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
using namespace std;


bool in_grid(int i, int j) {
    return !(i < 0 || j < 0 || i >= 10 || j >= 10);
}

void step(int i, int j, int** grid[10], int** flashed[10], int* flashes) {
    // increase self
    // flash (maybe)
    // call neighbours
    
    *grid[i][j]++;
    cout << *grid[i][j] << '\n';
    if (*grid[i][j] > 9 && !*flashed[i][j]) {
        *flashed[i][j] = 1;
        *flashes++;
        for (int in=i-1; in<=i+1; in++) {
            for (int jn=j-1; jn<=j+1; j++) {
                if (!(in == i && jn == j) && in_grid(in, jn)) {
                    *grid[in][jn]++;
                }
            }
        }
    }
    for (int in=i-1; in<=i+1; in++) {
        for (int jn=j-1; jn<=j+1; j++) {
            if (!(in == i && jn == j) && in_grid(in, jn)) {
                step(in, jn, grid, flashed, flashes);
            }
        }
    }
}

void flash(int** grid, int** flashed, int* flashes) {
    for (int i=0; i<10; i++) {
        for (int j=0; j<10; j++) {
            if (grid[i][j] > 9 && flashed[i][j] == 0) {
                flashed[i][j]++;
                 *flashes++;
                for (int in=i-1; in<=i+1; in++) {
                    for (int jn=j-1; jn<=j+1; j++) {
                        if (!(in == i && jn == j) && in_grid(in, jn)) {
                            grid[in][jn]++;
                        }
                    }
                }
            }
        }
    }    
}


bool flashing(int* grid[10], int* flashed[10]) {
    for (int i=0; i<10; i++) {
        for (int j=0; j<10; j++) {
            if (grid[i][j] > 9 && !flashed[i][j]) { return true; }
        }
    }
    return false;
}

void increment(int** grid) {
    for (int i=0; i<10; i++) {
        for (int j=0; j<10; j++) {
            grid[i][j] = grid[i][j] + 1;
        }
    }
}

void reset_grid(int** grid) {
    for (int i=0; i<10; i++) {
        for (int j=0; j<10; j++) {
            grid[i][j] = 0;
        }
    }
}

void print_grid(int** grid) {
    for (int i=0; i<10; i++) {
        for (int j=0; j<10; j++) {
            cout << grid[i][j];
        }
        cout << '\n';
    }
}

int main() {
    const int gridsize = 10;
    const int steps = 100;

    ifstream input("input.txt");
    string line;
    int** grid = new int*[gridsize];
    int** flashed = new int*[gridsize];

    //int grid[gridsize][gridsize];
    //int flashed[gridsize][gridsize];
    //int zeros[gridsize][gridsize] = {0};
    int* flashes = new int;
    *flashes = 0;

    for(int i=0; i<gridsize; i++) {
        flashed[i] = new int[gridsize];
        grid[i] = new int[gridsize];
        getline(input, line);
        for (int j=0; j<gridsize; j++) {
            grid[i][j] = line[j] - '0';
        }
    }
    
    // print_grid(grid);

    auto start = std::chrono::high_resolution_clock::now();

    // loop and set energy > 9 to 0
    for (int i=0; i<steps; i++) {
        cout << i << '\n';
        // Reset grid
        reset_grid(flashed);
        print_grid(grid);

        // Increment
        increment(grid);
        print_grid(grid);

        // Flash
        while (flashing(grid, flashed)) {
            
            flash(grid, flashed, flashes);
        }
        
    }

    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();

    cout << *flashes << '\n';
    cout << "Execution time: " << microseconds << '\n';
}