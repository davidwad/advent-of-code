#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int bin2dec(int arr[], int len) {
    int dec = 0;
    for (int i = 0; i < len; i++) {
        dec = 2 * dec + arr[i];
    }
    return dec;
}

vector <string> filter(vector <string> lines, int idx, int value) {
    vector <string> newlines;
    string line;
    for (int i = 0; i < lines.size(); i++) {
        line = lines.at(i);
        if (line[idx] - '0' == value) {
            newlines.push_back(line);
        }
    }
    return newlines;
}

int mostCommon(vector <string> lines, int idx, int prefer) {
    int ones = 0;
    int size = lines.size();
    for (int i = 0; i < size; i++) {
        if (lines.at(i)[idx] == '1') {
            ones++;
        }
    }
    if (2 * ones == size) {
        return prefer;
    } else if (2 * ones > size) {
        return 1;
    } else {
        return 0;
    }
}


int main() {
    ifstream input ("input.txt");
    string line;
    int len = 12;
    int common;
    vector <string> oxygen;
    vector <string> co2;
    while (getline(input, line)) {
        oxygen.push_back(line);
        co2.push_back(line);
    }

    int i = 0;
    while (oxygen.size() > 1) {
        common = mostCommon(oxygen, i, 1);
        oxygen = filter(oxygen, i, common);
        i++;
        cout << to_string(common);
    }
    cout << '\n';
    i = 0;
    while (co2.size() > 1) {
        common = mostCommon(co2, i, 1);
        co2 = filter(co2, i, !common);
        i++;
        cout << to_string(!common);
    }
    cout << '\n';

    int oxyarr[12];
    int co2arr[12];
    for (int i = 0; i < len; i++) {
        if (oxygen.at(0)[i] == '1') {
            oxyarr[i] = 1;
        } else {
            oxyarr[i] = 0;
        }
        cout << oxyarr[i];
    }
    cout << '\n';
    for (int i = 0; i < len; i++) {
        if (co2.at(0)[i] == '1') {
            co2arr[i] = 1;
        } else {
            co2arr[i] = 0;
        }
        cout << co2arr[i];
    }
    cout << '\n';

    cout << to_string( bin2dec(oxyarr, len) * bin2dec(co2arr, len) ) << '\n';

}


// int main() {
//     ifstream input ("input.txt");
//     string line;
//     int numlines = 0;
//     int len = 12;
//     int ones[len] = { 0 };
//     int gamma[len];
//     int epsilon[len];

//     while (getline(input, line)) {
//         numlines++;
//         for (int i = 0; i < len; i++) {
//             cout << line[i];
//             if (line[i] == '1') {
//                 ones[i] = ones[i] + 1;
                
//             }
            
//         }
//         cout << '\n';
//     }
//     for (int i = 0; i < len; i++) {
//         if (ones[i] * 2 >= numlines) {
//             gamma[i] = true;
//             epsilon[i] = false;
//         } else {
//             gamma[i] = false;
//             epsilon[i] = true;
//         }
//     }
//     cout << to_string( bin2dec(gamma, len) * bin2dec(epsilon, len) ) << '\n';


// }