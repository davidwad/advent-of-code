
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <cmath>
#include <chrono>
using namespace std;

/*
xdot_min = 2 * sqrt(x_min)
xdot_max = x_max + 1;
start from ydot=1.
end when overshooting.
*/

class Probe {
    public:
        int xpos = 0;
        int ypos = 0;
        int xvel;
        int yvel;
        int steps = 0;

        Probe(int xv, int yv) {
            xvel = xv;
            yvel = yv;
        }

        void update() {
            xpos += xvel;
            ypos += yvel;
            if (xvel > 0) { xvel--; }
            yvel--;
        }

        bool passed_target(int xmax, int ymin) {
            return xpos > xmax || ypos < ymin;
        }

        bool overshoot(int xmax, int ymax) {
            return xpos > xmax && ypos > ymax;
        }

        bool undershoot(int xmin, int ymin) {
            return xpos < xmin && ypos < ymin;
        }

        bool inside_target(int xrange[2], int yrange[2]) {
            return xpos <= xrange[1] && xpos >= xrange[0] && ypos <= yrange[1] && ypos >= yrange[0];
        }

        void simulate(int xrange[2], int yrange[2]) {
            while (!(inside_target(xrange, yrange) || passed_target(xrange[1], yrange[0]))) {
                // cout << xpos << ',' << ypos << '\n';
                update();
                steps++;
            }
        }

};

bool valid_ydot(int ydot, int ymin, int ymax) {
    int step = 1;
    while (true) {
        int alpha = ydot - (step * step + step)/2;
        if (!(ymin <= alpha && alpha <= ymax)) { return true; }
        if (alpha > ymax) { return false; }
        step++;
    }
}

int highest(int xrange[2], int yrange[2]) {
    int xmin = xrange[0];
    int xmax = xrange[1];
    int ymin = yrange[0];
    int ymax = yrange[1];

    int xdot_min = (int) sqrt(2 * xmin); 
    int xdot_max = xmax;
    
    int highest = 0;

    for (int xdot=xdot_min; xdot<=xdot_max; xdot++) {
        int ydot = 1;
        while (true) {
            Probe p(xdot, ydot);
            p.simulate(xrange, yrange);
            if (p.inside_target(xrange, yrange)) {
                if (ydot > highest) {
                    highest = ydot;
                }
            //} else if (p.overshoot(xmax, ymax) || p.undershoot(xmin, ymin)) {
            } else if (ydot > 10000) {
                //cout << p.xpos << ',' << p.ypos << '\n';
                break;
            }
            ydot++;
        }
    }
    return highest;
}

// int highest(int xrange[2], int yrange[2]) {
//     int xmin = xrange[0];
//     int xmax = xrange[1];
//     int ymin = yrange[0];
//     int ymax = yrange[1];
//     int highest = 0;

//     for (int xdot=1; xdot <= xmax; xdot++) {
//         int ydot = 1;
//         while (true) {
//             int step = 0;
//             while (true) {
//                 int alpha = ydot - (step*step + step)/2;
//                 if (ymin <= alpha && alpha <= ymax) {
//                     if (ydot > highest) {
//                         highest = ydot;
//                     } 
//                 }
//             }
//             ydot++;
//         }
//         xdot++;
//     }
// }

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
    int xmin = xrange[0];
    int xmax = xrange[1];
    int ymin = yrange[0];
    int ymax = yrange[1];
    for (int y=0; y>=ymin; y--) {
        for (int x=0; x<=xmax; x++) {
            if (x <= xmax && x >= xmin && y <= ymax && y >= ymin) {
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

    // for (int r : ranges) {
    //     cout << r << '\n';
    // }

    //print_target(xrange, yrange);
    auto start = std::chrono::high_resolution_clock::now();

    int ymax = highest(xrange, yrange);

    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();

    cout << ymax << '\n';
    cout << "Execution time: " << microseconds << '\n';
}