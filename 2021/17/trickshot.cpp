
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <cmath>
#include <chrono>
using namespace std;


class Probe {
    public:
        int xpos = 0;
        int ypos = 0;
        int xvel;
        int yvel;
        int ymax = 0;

        Probe(int xv, int yv) {
            xvel = xv;
            yvel = yv;
        }

        void update() {
            xpos += xvel;
            ypos += yvel;
            if (xvel > 0) { xvel--; }
            yvel--;
            if (ypos > ymax) {
                ymax = ypos;
            }
        }

        bool passed_target(int xmax, int ymin) {
            return xpos > xmax || ypos < ymin;
        }

        bool inside_target(int xrange[2], int yrange[2]) {
            return xpos <= xrange[1] && xpos >= xrange[0] && ypos <= yrange[1] && ypos >= yrange[0];
        }

        void simulate(int xrange[2], int yrange[2]) {
            while (!(inside_target(xrange, yrange) || passed_target(xrange[1], yrange[0]))) {
                // cout << xpos << ',' << ypos << '\n';
                update();
            }
        }

};

int highest(int xrange[2], int yrange[2]) {
    int highest = 0;
    int alpha;
    int beta;

    int x_min = xrange[0];
    int x_max = xrange[1];
    int y_min = yrange[0];
    int y_max = yrange[1];

    int xdot_min = (int)(sqrt((double)x_min + 1/4) - 1/2); 
    int xdot_max = x_max;
    //cout << xdot_min << ',' << xdot_max << '\n';

    for (int xdot=xdot_min; xdot<=xdot_max; xdot++) {

        int ydot_min = 1 - y_max;
        int ydot_max = 1 - y_min;

        for (int ydot = ydot_min; ydot<=ydot_max; ydot++) {
            
            Probe p(xdot, ydot);
            p.simulate(xrange, yrange);
            //cout << xdot << ',' << ydot << ": ";
            if (p.inside_target(xrange, yrange)) {
                //cout << "hit" << '\n';
                if (p.ymax > highest) {
                    highest = p.ymax;
                }
            } 
        }
    }
    return highest;
}


vector<int> read_input(string line) {
    vector<int> ranges;
    string substr = "";
    int i = 0; 
    while (i < line.length()) {
        char c = line[i];
        
        if (isdigit(c) || c == '-') {
            
            substr.push_back(c);
        } else {
            if (!substr.empty()) {
                ranges.push_back(stoi(substr, nullptr));
                substr = "";
            }
        }
        i++;
    }
    ranges.push_back(stoi(substr, nullptr));
    return ranges;
}


void print_target(int xrange[2], int yrange[2]) {
    int x_min = xrange[0];
    int x_max = xrange[1];
    int y_min = yrange[0];
    int y_max = yrange[1];
    for (int y=0; y>=y_min; y--) {
        for (int x=0; x<=x_max; x++) {
            if (x <= x_max && x >= x_min && y <= y_max && y >= y_min) {
                cout << '#';
            } else {
                cout << '.';
            }
        }
        cout <<'\n';
    }
}

int main() {
    ifstream input("input.txt");
    string line;
    int xrange[2];
    int yrange[2];

    getline(input, line);
    vector<int> ranges = read_input(line);
    xrange[0] = ranges.at(0);
    xrange[1] = ranges.at(1);
    yrange[0] = ranges.at(2);
    yrange[1] = ranges.at(3);

    auto start = std::chrono::high_resolution_clock::now();

    int y_max = highest(xrange, yrange);

    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();

    cout << y_max << '\n';
    cout << "Execution time: " << microseconds << '\n';
}