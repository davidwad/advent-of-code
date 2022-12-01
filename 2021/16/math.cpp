
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <chrono>
using namespace std;


class Packet {
    public:
        unsigned long long int value = 0;
        int length = 0;
};

void add_bits(unsigned int n, vector<int>& bits) {
    for (int i = 3; i >= 0; i--) {
        int k = n >> i;
        if (k & 1) {
            bits.push_back(1);
        } else {
            bits.push_back(0);
        }
    }
}

string read_bits(std::vector<int>::iterator& it, int n) {
    string str;
    for (int i = 0; i < n; i++) {
        str.push_back(*it + '0');
        it++;
    }
    return str;
}

Packet read_literal(std::vector<int>::iterator& it) {
    Packet lit;
    string str;
    int cont = 1;
    while (cont) {
        cont = stoi(read_bits(it, 1), nullptr, 2);
        str.append(read_bits(it, 4));
        lit.length += 5;
    }
    lit.value = stoull(str, nullptr, 2);
    return lit;
}

void print(int level, string desc, unsigned long long int value) {
    for (int i = 0; i < level; i++) {
        cout << "  ";
    }
    cout << desc << ": " << value << '\n';
}

Packet read_packet(std::vector<int>::iterator& it, int& vsum, int level) {
    Packet p;
    cout << "--------------------------------------------------------------" << '\n';

    int version = stoi(read_bits(it, 3), nullptr, 2);
    vsum += version;
    p.length += 3;
    print(level, "Version", version);

    int type_id = stoi(read_bits(it, 3), nullptr, 2);
    p.length += 3;
    print(level, "Type ID", type_id);

    if (type_id == 4) {
        Packet lit = read_literal(it);
        p.length += lit.length;
        p.value = lit.value;

        print(level, "Literal", lit.value);
    } else {
        int length_type_id = stoi(read_bits(it, 1), nullptr, 2);
        p.length += 1;
        print(level, "Length type ID", length_type_id);

        vector<Packet> subpackets;
        if (length_type_id == 0) {
            int sub_length = stoi(read_bits(it, 15), nullptr, 2);
            p.length += 15;
            print(level, "Sub length", sub_length);

            int counter = 0;
            while (counter < sub_length) {
                Packet sub = read_packet(it, vsum, level + 1);
                counter += sub.length;
                subpackets.push_back(sub);
            }
            p.length += sub_length;
        } else {
            int sub_packets = stoi(read_bits(it, 11), nullptr, 2);
            p.length += 11;
            print(level, "Sub packets", sub_packets);
            for (int i = 0; i < sub_packets; i++) {
                Packet sub = read_packet(it, vsum, level + 1);
                p.length += sub.length;
                subpackets.push_back(sub);
            }
        }
        switch (type_id) {
            case 0: {
                unsigned long long int sum = 0;
                for (Packet s : subpackets) {
                    sum += s.value;
                }
                p.value = sum;
                break;
            }
            case 1: {
                unsigned long long int prod = 1;
                for (Packet s : subpackets) {
                    prod *= s.value;
                }
                p.value = prod;
                break;
            }
            case 2: {
                unsigned long long int min = UINT64_MAX;
                for (Packet s : subpackets) {
                    if (s.value < min) {
                        min = s.value;
                    }
                }
                p.value = min;
                break;
            }
            case 3: {
                unsigned long long int max = 0;
                for (Packet s : subpackets) {
                    if (s.value > max) {
                        max = s.value;
                    }
                }
                p.value = max;
                break;
            }
            case 5: {
                p.value = (unsigned long long int) subpackets[0].value > subpackets[1].value;
                break;
            }
            case 6: {
                p.value = (unsigned long long int)subpackets[0].value < subpackets[1].value;
                break;
            }
            case 7: {
                p.value = (unsigned long long int)subpackets[0].value == subpackets[1].value;
                break;
            }
        }
    }
    return p;
}

int main() {
    ifstream input("input.txt");
    string line;
    vector<int> bits;
    int vsum = 0;
    int level = 0;

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
    Packet res = read_packet(it, vsum, level);

    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();

    cout << "--------------------------------------------------------------" << '\n';
    print(level, "Packet value", res.value);
    print(level, "Execution time", microseconds);
}