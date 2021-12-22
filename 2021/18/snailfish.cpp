#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
using namespace std;


enum direction {left, right};

int gid = 0;

class Pair {
    public:
        Pair* left = nullptr;
        Pair* right = nullptr;
        bool singular;
        int value;
        int depth;
        int id;

        Pair() { id = gid++; }
};

void sort_regulars(Pair* p, vector<Pair*>& regs) {
    if (p->singular) {
        regs.push_back(p);
    } else {
        sort_regulars(p->left, regs);
        sort_regulars(p->right, regs);
    }
}

Pair* get_adjacent(int id, direction dir, vector<Pair*> pairs) {
    for (int i = 0; i < pairs.size(); i++) {
        Pair* p = pairs[i];
        if (p->id == id) {
            if (dir == direction::left) {
                if (i == 0) {
                    return nullptr;
                } else {
                    return pairs[i-1];
                }
            } else {
                if (i == pairs.size()-1) {
                    return nullptr;
                } else {
                    return pairs[i+1];
                }                
            }
        }
    }
    return nullptr;
}

void split(Pair* p) {
    p->singular = false;

    Pair pl;
    pl.singular = true;
    pl.value = p->value/2;
    p->left = (Pair*) malloc(sizeof(Pair));
    *p->left = pl;
    
    Pair pr;
    pr.singular = true;
    pr.value = (p->value + 1)/2;
    p->right = (Pair*) malloc(sizeof(Pair));
    *p->right = pr;
}

bool find_splits(vector<Pair*> regs) {
    for (Pair* p : regs) {
        if (p->value >= 10) {
            split(p);
            return true;
        }
    }
    return false;
}

void explode(Pair* p, Pair* root) {
    vector<Pair*> regs;
    sort_regulars(root, regs);

    int lval = p->left->value;
    int lid = p->left->id;
    int rval = p->right->value;
    int rid = p->right->id;

    // Turn pair into number
    p->left = nullptr;
    p->right = nullptr;
    p->singular = true;
    p->value = 0;

    Pair* lp = get_adjacent(lid, direction::left, regs);
    if (lp != nullptr) {
        lp->value += lval;
    }
    Pair* rp = get_adjacent(rid, direction::right, regs);
    if (rp != nullptr) {
        rp->value += rval;
    }
}

void find_explosions(Pair* p, Pair* root, int maxdepth, int depth, bool& exploded) {
    if (p->singular) { return; }
    if (depth >= maxdepth) {
        exploded = true;
        explode(p, root);
    } else {
        find_explosions(p->left, root, maxdepth, depth + 1, exploded);
        find_explosions(p->right, root, maxdepth, depth + 1, exploded);
    }
}

int magnitude (Pair* p) {
    if (p->singular) {
        return p->value;
    } else {
        return 3 * magnitude(p->left) + 2 * magnitude(p->right);
    }
}

Pair parse_string(string str, Pair* parent) {
    //cout << str << '\n';
    Pair p;

    int bcounter = 0;
    vector<char> charstack;
    if (str.size() == 1) {
        p.value = str[0] - '0';
        p.singular = true;
    }
    for (int i = 0; i < str.length(); i++) {
        char c = str[i];
        if (c == '[') {
            bcounter++;
        } else if (c == ']') {
            bcounter--;
        } else if (c == ',' && bcounter == 1) {
            p.singular = false;
            p.left = (Pair*) malloc(sizeof(Pair));
            p.right = (Pair*) malloc(sizeof(Pair));
            *p.left = parse_string(str.substr(1, i-1), &p);
            *p.right = parse_string(str.substr(i+1, str.size() - i - 2), &p);
            
        }
    }
    return p;
}

Pair pairsum(Pair p1, Pair p2) {
    Pair p;
    p.left = (Pair*) malloc(sizeof(Pair));
    p.right = (Pair*) malloc(sizeof(Pair));
    *p.left = p1;
    *p.right = p2;
    p.singular = false;
    return p;
}

void print_pair(Pair p) {
    if (p.singular) {
        cout << p.value;
    } else {
        cout << '[';
        print_pair(*p.left);
        cout << ',';
        print_pair(*p.right);
        cout << ']';
    }
}

int main() {
    const int maxdepth = 4;
    ifstream input("input.txt");
    string line;
    Pair p;
    int magnitude_;

    getline(input, line);
    p = parse_string(line, nullptr);
    while (getline(input, line)) {
        p = pairsum(p, parse_string(line, nullptr));
        print_pair(p);
        cout << '\n';
        bool exploded = true;
        bool split = true;
        while (exploded || split) {
            exploded = true;      
            split = false;
            while (exploded) {
                exploded = false;
                find_explosions(&p, &p, maxdepth, 0, exploded);
            }
            if (!exploded) {
                vector<Pair*> regs;
                sort_regulars(&p, regs);
                split = find_splits(regs);
            }
        }
        print_pair(p);
        cout << '\n';
    }
    magnitude_ = magnitude(&p);
    
    auto start = std::chrono::high_resolution_clock::now();

    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();

    cout << magnitude_ << '\n';
    cout << "Execution time: " << microseconds << '\n';
}