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

bool same_string(string str1, string str2) {
    if (str1.length() != str2.length()) { return false; }
    for (char c : str1) {
        if(str2.find(c) == std::string::npos) { return false; }
    }
    return true;
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


/*
1, 4, 7, 8 is free and gives a
Out of (2, 3, 5), only 3 contains c and f which are known.
Out of (0, 6, 9), only 6 DOES NOT contain c and f which are known.
Out of (2, 5), only 5 contains b and d which are known.
Out of (0, 9), only 9 contains b and d which are known.
*/

int main() {
    ifstream input("input.txt");
    string line;
    vector<vector<string>> pline;
    vector<vector<string>> inputs;
    vector<vector<string>> outputs;
    vector<list<int>> digmaps;
    int sum = 0;
    while(getline(input, line)) {
        pline = parse_line(line);
        inputs.push_back(pline.at(0));
        outputs.push_back(pline.at(1));
    }
    //print_input(inputs, outputs);
    auto start = std::chrono::high_resolution_clock::now();

    for (int l = 0; l < inputs.size(); l++) {
        reset_mappool(&digmaps, 10);
        vector<string> digmap;
        vector<string> input = inputs.at(l);
        vector<string> output = outputs.at(l);
        char cf[2];
        char bd[2];
        string str_4;
        for (int i = 0; i < input.size(); i++) {
            string digstr = input.at(i);
            switch (digstr.length()) {
                case 2:
                    cf[0] = digstr[0];
                    cf[1] = digstr[1];
                    digmaps.at(1).push_back(i);
                    break;
                case 3:
                    digmaps.at(7).push_back(i);
                    break;
                case 4:
                    str_4 = digstr;
                    digmaps.at(4).push_back(i);
                    break;
                case 7:
                    digmaps.at(8).push_back(i);
                    break;
                case 5:
                    digmaps.at(2).push_back(i);
                    digmaps.at(3).push_back(i);
                    digmaps.at(5).push_back(i);
                    break;
                case 6:
                    digmaps.at(0).push_back(i);
                    digmaps.at(6).push_back(i);
                    digmaps.at(9).push_back(i);
                    break;
            }
        }
        int idx = 0;
        for (char c : str_4) {
            if (c != cf[0] && c != cf[1]) {
                bd[idx] = c;
                idx++;
            }
        }

        bool abort = false;
        for (int n : {2, 3, 5}) {
            if (abort) { break; }
            for (int i : digmaps.at(n)) {
                string str = input.at(i);
                if (str.find(cf[0]) != std::string::npos && str.find(cf[1]) != std::string::npos) {
                    digmaps.at(3).clear();
                    digmaps.at(3).push_back(i);
                    digmaps.at(2).remove(i);
                    digmaps.at(5).remove(i);
                    abort = true;
                    break;
                }
            }
        }

        abort = false;
        for (int n : {2, 5}) {
            if (abort) { break; }
            for (int i : digmaps.at(n)) {
                string str = input.at(i);
                if (str.find(bd[0]) != std::string::npos && str.find(bd[1]) != std::string::npos) {
                    digmaps.at(5).clear();
                    digmaps.at(5).push_back(i);
                    digmaps.at(2).remove(i);
                    abort = true;
                    break;
                }
            }
        }

        abort = false;
        for (int n : {0, 6, 9}) {
            if (abort) { break; }
            for (int i : digmaps.at(n)) {
                string str = input.at(i);
                if (!(str.find(cf[0]) != std::string::npos && str.find(cf[1]) != std::string::npos)) {
                    digmaps.at(6).clear();
                    digmaps.at(6).push_back(i);
                    digmaps.at(0).remove(i);
                    digmaps.at(9).remove(i);
                    abort = true;
                    break;
                }
            }
        }
        abort = false;
        for (int n : {0, 9}) {
            if (abort) { break; }
            for (int i : digmaps.at(n)) {
                string str = input.at(i);
                if (str.find(bd[0]) != std::string::npos && str.find(bd[1]) != std::string::npos) {
                    digmaps.at(9).clear();
                    digmaps.at(9).push_back(i);
                    digmaps.at(0).remove(i);
                    abort = true;
                    break;
                }
            }
        }
        //print_mappool(digmaps);
        string res = "";
        for (string str_o: output) {
            
            for (int i = 0; i < digmaps.size(); i++) {
                string str_i = input.at(digmaps.at(i).front());
                //cout << str_o << ", " << str_i << '\n';
                if (same_string(str_o, str_i)) {
                    res.push_back(i + '0');
                    //cout << res << '\n';
                }
            }
        }
        //cout << res << '\n';
        sum += stoi(res, nullptr);
    }

    


    
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    cout << sum << '\n';
    cout << "Execution time: " << microseconds << '\n';
}