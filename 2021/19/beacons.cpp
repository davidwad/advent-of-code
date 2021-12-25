#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
using namespace std;


const string FILENAME = "exampleinput.txt";

class Point {
    public:
        int x1, x2, x3;

        Point () {}

        Point(int x1_, int x2_, int x3_) {
            x1 = x1_;
            x2 = x2_;
            x3 = x3_;
        }

        bool operator== (const Point& p) {
            return x1 == p.x1 && x2 == p.x2 && x3 == p.x3;
        }

        Point operator+ (const Point& p) {
            return Point(x1 + p.x1, x2 + p.x2, x3 + p.x3);
        }

        Point operator- (const Point& p) {
            return Point(x1 - p.x1, x2 - p.x2, x3 - p.x3);
        }

        void print() {
            cout << x1 << ',' << x2 << ',' << x3 << '\n';
        }
};

class Scanner {
    public:
        int idx;
        Point pos;
        vector<Point> beacons;

        Scanner() {}

        void print() {
            cout << "Scanner " << idx << ':' << '\n';
            for (Point p : beacons) {
                cout << '\t';
                p.print();
            }
        }
};

Point read_line(string line) {
    int coords[3];
    string substr;

    int idx = 0;
    int i = 0;
    while (i < line.length()) {
        char c = line[i];
        
        if (isdigit(c) || c == '-') {
            
            substr.push_back(c);
        } else {
            if (!substr.empty()) {
                coords[idx++] = stoi(substr, nullptr);
                substr = "";
            }
        }
        i++;
    }
    coords[idx++] = stoi(substr, nullptr);
    return Point(coords[0], coords[1], coords[2]);
}

vector<Scanner> parse_input() {
    ifstream input(FILENAME);
    string line;
    vector<Scanner> scanners;

    int idx = 0;
    Scanner scan;
    while (getline(input, line)) {
        if (line.substr(0, 3) == "---") {
            Scanner temp;
            scan = temp;
            scan.idx = idx++;
        } else if (line.length() > 5) {
            scan.beacons.push_back(read_line(line));
        } else {
            scanners.push_back(scan);
        }
    }
    scanners.push_back(scan);
    return scanners;
}


/*
for each scanner s1:
    subtract first coordinates (X1 = X1 - X1(0))
    for each rotation:
        for each scanner s2:
            subtract first coordinates (X2 = X2 - X2(0))
            if X1 and X2 have 12 coords in common:
                relative position of s1 and s2 is X1(0) - X2(0)
        

*/

int main() {
    vector<Scanner> scanners;

    scanners = parse_input();

    for (Scanner s : scanners) {
        s.print();
    }
    auto start = std::chrono::high_resolution_clock::now();

    for (Scanner s1 : scanners) {
        for (Scanner s2 : scanners) {
            if (s1.idx = s2.idx) { continue; }
        }
    }

    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();

    // cout << maxmagn << '\n';
    cout << "Execution time: " << microseconds << '\n';
}