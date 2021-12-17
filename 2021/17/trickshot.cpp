
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <chrono>
using namespace std;


class Probe {
    public:
        int xpos;
        int ypos;
        int xvel;
        int yvel;

        Probe(int x, int y, int xv, int yv) {
            xpos = x;
            ypos = y;
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
            return (xpos > xmax || ypos < ymin);
        }

};


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
    const int subsize = 100;
    const int gridsize = subsize * 5;

    ifstream input("exampleinput.txt");
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

    print_target(xrange, yrange);
    auto start = std::chrono::high_resolution_clock::now();

    for (int yvel=10; y >)
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();

    //cout << dest.d << '\n';
    cout << "Execution time: " << microseconds << '\n';
}