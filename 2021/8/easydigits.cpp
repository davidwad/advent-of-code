#include <iostream>
#include <fstream>
#include <string>
#include <vector>
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


int main() {
    ifstream input("input.txt");
    string line;
    int ezcount = 0;;
    int segments[10];
    vector<vector<string>> pline;
    vector<vector<string>> inputs;
    vector<vector<string>> outputs;
    while(getline(input, line)) {
        pline = parse_line(line);
        inputs.push_back(pline.at(0));
        outputs.push_back(pline.at(1));
    }
    print_input(inputs, outputs);

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < inputs.size(); i++) {
        vector<string> input = inputs.at(i);
        vector<string> output = outputs.at(i);
        int strlen;
        string digstr;
        for (int j = 0; j < output.size(); j++) {
            digstr = output.at(j);
            strlen = digstr.length();
            if (strlen == 2 || strlen == 3 || strlen == 4 || strlen == 7) {
                ezcount++;
            }
        }
    }

    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    cout << ezcount << '\n';
    cout << "Execution time: " << microseconds << '\n';
}