
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <chrono>
using namespace std;


void add_bits(unsigned int n, vector<int>& bits) {
    for (int i = 3; i >= 0; i--) {
        int k = n >> i;
        if (k & 1) {
            //cout << "1";
            bits.push_back(1);
        } else {
            //cout << "0";
            bits.push_back(0);
        }
    }
    //cout << '\n';
}

string read_bits(std::vector<int>::iterator& it, int n) {
    string str;
    for (int i = 0; i < n; i++) {
        str.push_back(*it + '0');
        it++;
    }
    //return stoi(bits, nullptr, 2);
    return str;
}

int read_literal(std::vector<int>::iterator& it, int& counter) {
    string str;
    int cont = 1;
    while (cont) {
        cont = stoi(read_bits(it, 1), nullptr, 2);
        str.append(read_bits(it, 4));
        counter += 5;
    }
    // while (counter % 4 != 0) {
    //     read_bits(it, 1);
    //     counter++;
    // }
    return stoi(str, nullptr, 2);
}

void print(string desc, int value) {
    cout << desc << ": " << value << '\n';
}

int read_packet(std::vector<int>::iterator& it, int& vsum) {
    int length = 0;
    cout << "-------------------------------" << '\n';

    int version = stoi(read_bits(it, 3), nullptr, 2);
    vsum += version;
    length += 3;
    print("Version", version);

    int type_id = stoi(read_bits(it, 3), nullptr, 2);
    length += 3;
    print("Type ID", type_id);

    if (type_id == 4) {
        print("Literal", read_literal(it, length));
    } else {
        int length_type_id = stoi(read_bits(it, 1), nullptr, 2);
        length += 1;
        print("Length type ID", length_type_id);

        if (length_type_id == 0) {
            int sub_length = stoi(read_bits(it, 15), nullptr, 2);
            length += 15;
            print("Sub length", sub_length);

            int counter = 0;
            while (counter < sub_length) {
                counter += read_packet(it, vsum);
            }
            if (counter != sub_length) {
                cout << '\n' << "WRONG COUNTER" << '\n';
                exit(1);
            } 
            length += sub_length;
        } else {
            int sub_packets = stoi(read_bits(it, 11), nullptr, 2);
            length += 11;
            print("Sub packets", sub_packets);
            for (int i = 0; i < sub_packets; i++) {
                length += read_packet(it, vsum);
            }
        }
    }
    return length;
}

int main() {
    ifstream input("input.txt");
    string line;
    vector<int> bits;
    int vsum = 0;

    getline(input, line);

    for (char c : line) {
        if (isdigit(c)) {
            add_bits(c - '0', bits);
        } else {
            add_bits(c - 'A' + 10, bits);
        }
    }

    auto start = std::chrono::high_resolution_clock::now();

    auto it = bits.begin();
    read_packet(it, vsum);

    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();

    cout << "-------------------------------" << '\n';
    print("Version sum", vsum);
    print("Execution time", microseconds);
}