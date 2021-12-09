#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <chrono>
using namespace std;


vector<vector<string>> parse_line(string line) {
    vector<vector<string>> ret;
    vector<string> inputs;
    vector<string> outputs;

    string substr = "";
    int i = 0; 
    char c = line[i]; 
    while (c != '|') {
        c = line[i];
        
        if (isalpha(c)) {
            substr.push_back(c);
        } else {
            if (!substr.empty()) {
                inputs.push_back(substr);
                substr = "";
            }
        }
        i++;
    }

    while (i < line.length()) {
        c = line[i];
        
        if (isalpha(c)) {
            substr.push_back(c);
        } else {
            if (!substr.empty()) {
                outputs.push_back(substr);
                substr = "";
            }
        }
        i++;
    }
    outputs.push_back(substr);

    ret.push_back(inputs);
    ret.push_back(outputs);
    return ret;
}

void reset_mappool(vector<list<int>>* mappool, int size) {
    vector<list<int>> newpool;
    for (int i = 0; i < size; i++) {
        list<int> map;
        
        // for (int j = 0; j < size; j++) {
        //     map.push_back(j);
        // }
        newpool.push_back(map);
    }
    *mappool = newpool;
}

void put_digit (list<int>* map, int digit) {
    list<int> m;
    m.push_back(digit);
    *map = m;
}

void print_input(vector<vector<string>> inputs, vector<vector<string>> outputs) {
    vector<string> input;
    vector<string> output;
    for (int i = 0; i < inputs.size(); i++) {
        input = inputs.at(i);
        output = outputs.at(i);
        for (int j = 0; j < input.size(); j++) {
            cout << input.at(j) << ' '; 
        }
        cout << "| ";
        for (int k = 0; k < output.size(); k++) {
            cout << output.at(k) << ' '; 
        }
        cout << '\n';
    }
}

void print_mappool(vector<list<int>> mappool) {
    vector<list<int>> newpool;
    for (list<int> map : mappool) {
        if (map.empty()) {
            cout << '-';
        } else {
            for (int i : map) {
                cout << i << ' ';
            }
        }
        cout << '\n';
    }
    cout << '\n';
}


int main() {
    ifstream input("input.txt");
    string line;
    vector<list<int>> alphamaps;
    vector<list<int>> digmaps;
    int sum = 0;
    int segments[10];
    vector<vector<string>> pline;
    vector<vector<string>> inputs;
    vector<vector<string>> outputs;
    while(getline(input, line)) {
        pline = parse_line(line);
        inputs.push_back(pline.at(0));
        outputs.push_back(pline.at(1));
    }
    //print_input(inputs, outputs);
    auto start = std::chrono::high_resolution_clock::now();


    for (int i = 0; i < inputs.size(); i++) {
        reset_mappool(&alphamaps, 7);
        reset_mappool(&digmaps, 10);
        vector<string> input = inputs.at(i);
        vector<string> output = outputs.at(i);
        int strlen;
        string digstr;
        for (int j = 0; j < input.size(); j++) {
            digstr = input.at(j);
            //cout << digstr << '\n';
            strlen = digstr.length();
            if (strlen == 2) {
                digmaps.at(1).push_back(j);
            } 
            else if (strlen == 3) {
                digmaps.at(7).push_back(j);
            } else if (strlen == 4) {
                digmaps.at(4).push_back(j);
            } else if (strlen == 7) {
                digmaps.at(8).push_back(j);
            } else if (strlen == 5) {
                digmaps.at(2).push_back(j);
                digmaps.at(3).push_back(j);
                digmaps.at(5).push_back(j);
            } else if (strlen == 6) {
                digmaps.at(0).push_back(j);
                digmaps.at(6).push_back(j);
                digmaps.at(9).push_back(j);
            }
            
        }
        string str_1 = input.at(digmaps.at(1).front());
        string str_4 = input.at(digmaps.at(4).front());
        string str_7 = input.at(digmaps.at(7).front());
        string str_8 = input.at(digmaps.at(8).front());

        // Get mapping x -> a
        for (char c : str_7) {
            if (str_1.find(c) == string::npos) {
                alphamaps.at('a' - 'a').push_back(c - 'a');
                break;
            }
        }

        // Get mapping (x,y) -> (c,f)
        for (char c : str_1) {
            alphamaps.at('c' - 'a').push_back(c - 'a');
            alphamaps.at('f' - 'a').push_back(c - 'a');
        }

        // Get mapping (x,y) -> (b, d)
        for (char c : str_4) {
            if (str_1.find(c) == string::npos) {
                alphamaps.at('b' - 'a').push_back(c - 'a');
                alphamaps.at('d' - 'a').push_back(c - 'a');  
            }
        }

        // Get mapping (x,y) -> (e.g)
        list<int> digs;
        for (int j = 0; j < 7; j++) {
            digs.push_back(j);
        }
        for (int j = 0; j < 7; j++) {
            for (int c : alphamaps.at(j)) {
                digs.remove(c);
            }
            
        }
        for (int c : digs) {
            alphamaps.at('e' - 'a').push_back(c);
            alphamaps.at('g' - 'a').push_back(c);
        }

        // Get mapping (x,y) -> (d,g) -> d, g
        string str_235 = input.at(digmaps.at(2).front());
        for (char c : str_235) {
            bool inall = true;
            for (int idx : digmaps.at(2)) {
                string str = input.at(idx);
                if (str.find(c) == string::npos) {
                    inall = false;
                }
            }
            if (inall) {
                // c exists in string 2, 3, and 5 => c is a, d or g
                if (alphamaps.at(c - 'a').size() != 1) {
                    // c is not a
                    
                    if (str_4.find(c) != string::npos) {
                        // c is d
                        alphamaps.at('d' - 'a').pop_back();
                        alphamaps.at('d' - 'a').pop_back();
                        alphamaps.at('d' - 'a').push_back(c - 'a');
                        alphamaps.at('b' - 'a').remove(c - 'a');
                    } else {
                        //c is g
                        alphamaps.at('g' - 'a').pop_back();
                        alphamaps.at('g' - 'a').pop_back();
                        alphamaps.at('g' - 'a').push_back(c - 'a');
                        alphamaps.at('e' - 'a').remove(c - 'a');
                    }
                    // for (char x : str_4) {
                    //     if (x == c) {
                    //         // c is d
                    //         // alphamaps.at('d' - 'a').pop_back();
                    //         // cout << '-' << '\n';
                    //         // alphamaps.at('d' - 'a').pop_back();
                    //         // cout << '-' << '\n';
                    //         alphamaps.at('d' - 'a').pop_back();
                    //         alphamaps.at('d' - 'a').pop_back();
                    //         alphamaps.at('d' - 'a').push_back(c - 'a');
                    //         alphamaps.at('b' - 'a').remove(c - 'a');
                    //     } else {  // c is g
                    //         // alphamaps.at('g' - 'a').pop_back();
                    //         // alphamaps.at('g' - 'a').pop_back();
                    //         // alphamaps.at('g' - 'a').push_back(c - 'a');
                    //         // alphamaps.at('e' - 'a').remove(c - 'a');
                    //     }
                    // }
                }
                // c is not a => c is d or g


            } 

        }
        //string str_069 = input.at(digmaps.at(0).front());
        for (int c : alphamaps.at('c' - 'a')) {
            bool inall = true;
            for (int idx : digmaps.at(0)) {
                string str = input.at(idx);
                if (str.find(c + 'a') == string::npos) {
                    inall = false;
                }
            }
            if (inall) {
                // c is c or f and exists in 0, 6 and 9 => c is f
                //cout << "yes" << '\n';
                alphamaps.at('f' - 'a').pop_back();
                alphamaps.at('f' - 'a').pop_back();
                alphamaps.at('f' - 'a').push_back(c);
                alphamaps.at('c' - 'a').remove(c); 
                break;
            }
        }

        print_mappool(digmaps);
        print_mappool(alphamaps);
        // if (i == 1) {
        //     break;
        // }
        // break;
    }
    
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    cout << sum << '\n';
    cout << "Execution time: " << microseconds << '\n';
}