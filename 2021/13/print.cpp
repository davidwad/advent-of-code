#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <set>
#include <chrono>
using namespace std;


class Point {
    public:
        int x;
        int y;

        Point(int x_, int y_) {
            x = x_;
            y = y_;
        }

        void fold_up(int yfold) {
            if (y > yfold) { y = 2 * yfold - y; }
        }

        void fold_left(int xfold) {
            if (x > xfold) { x = 2 * xfold - x; }
        }
};

bool same_point (Point p1, Point p2)
{ return (p1.x == p2.x && p1.y == p2.y ); }


void print_points(list<Point*> points) {
    int xmax = INT32_MIN;
    int ymax = INT32_MIN;
    for (Point* p : points) {
        if (p->x > xmax) {xmax = p->x;}
        if (p->y > ymax) {ymax = p->y;}
    }
    int grid[ymax+2][xmax+2] = {0};
    for (Point* p : points) {
        grid[p->y][p->x] = 1;
    }
    for (int i = 0; i <= ymax+1; i++) {
        for (int j = 0; j <= xmax+1; j++) {
            if (grid[i][j]) {
                cout << '#';
            } else {
                cout << ' ';
            }
        }
        cout << '\n';
    }
}


int main() {
    ifstream input("input.txt");
    string line;
    list<Point*> points;
    list<Point> unique;


    while(getline(input, line)) {
        string x;
        string y;
        string substr = "";
        int i = 0; 
        char c = line[i];
        if (line.length() < 1) { break; }
        while (i < line.length()) {
            c = line[i];
            
            if (isdigit(c)) {
                substr.push_back(c);
            } else {
                x = substr;
                substr = "";
            }
            i++;
        }
        y = substr;
        Point* ptr = (Point*) malloc(sizeof(Point));
        *ptr = Point(stoi(x, nullptr), stoi(y, nullptr));
        points.push_back(ptr);
    }

    auto start = std::chrono::high_resolution_clock::now();

    while(getline(input, line)) {
        int coord;
        string str;
        for (int i = 13; i < line.length(); i++) {
            str.push_back(line[i]);
        }
        coord = stoi(str, nullptr);
        if (line[11] == 'x') {
            for (Point* p : points) {
                p->fold_left(coord);
            }
        } else if (line[11] == 'y') {
            for (Point* p : points) {
                p->fold_up(coord);
            }
        }
    }

    // for (Point* ptr : points) {
    //     bool add = true;
    //     for (Point p : unique) {
    //         if (same_point(*ptr, p)) {
    //             add = false;
    //             break;
    //         }
    //     }
    //     if (add) {
    //         unique.push_back(*ptr);
    //     }
    // }

    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();

    print_points(points);
    cout << "Execution time: " << microseconds << '\n';
}