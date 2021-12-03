#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int bin2dec(int arr[], int len) {
    int dec = 0;
    for (int i = 0; i < len; i++) {
        dec = 2 * dec + arr[i];
    }
    return dec;
}

int main() {
    ifstream input ("input.txt");
    string line;
    int numlines = 0;
    int len = 12;
    int ones[len] = { 0 };
    int gamma[len];
    int epsilon[len];

    while (getline(input, line)) {
        numlines++;
        for (int i = 0; i < len; i++) {
            cout << line[i];
            if (line[i] == '1') {
                ones[i] = ones[i] + 1;
                
            }
            
        }
        cout << '\n';
    }

    for (int i = 0; i < len; i++) {
        if (ones[i] * 2 >= numlines) {
            gamma[i] = true;
            epsilon[i] = false;
        } else {
            gamma[i] = false;
            epsilon[i] = true;
        }
    }

    cout << to_string( bin2dec(gamma, len) * bin2dec(epsilon, len) ) << '\n';
}