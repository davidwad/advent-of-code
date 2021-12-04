#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

vector<int> readNumbers(string line, char sep) {
    char c;
    string str;
    int n = line.length();
    vector<int> numbers;
    int j = 0;

    for (int i = 0; i < n; i++) {
        c = line[i];

        if (c == sep || i == n - 1) {
            if (i == 0 || line[i-1] == ' ') {
                continue;
            }
            str = line.substr(i - j, j);
            numbers.push_back(stoi(str));
            j = 0;
        } else {
            j++;
        }
    }
    return numbers;
}

vector<vector<int>> readBoard(ifstream* input, int size) {
    string line;
    vector<int> row;
    vector<vector<int>> board;

    for (int h = 0; h < size; h++) {
        getline(*input, line);
        board.push_back(readNumbers(line, ' '));
    }
    return board;
}

vector<vector<vector<int>>> initBoards(int numboards, int size) {
    vector<int> row;
    vector<vector<int>> board;
    vector<vector<vector<int>>> boards;

    for (int i = 0; i < size; i++) {
        row.push_back(0);
    }
    for (int i = 0; i < size; i++) {
        board.push_back(row);
    }
    for (int i = 0; i < numboards; i++) {
        boards.push_back(board);
    }
    return boards;
}

bool checkBingo(vector<vector<int>> board) {
    int sum;

    // Check rows
    for (int i = 0; i < board.size(); i++) {
        sum = 0;
        //row = board.at(i);
        for (int j = 0; j < board.at(0).size(); j++) {
            sum += board.at(i).at(j);
        }
        if (sum == 5) {
            return true;
        }
    }

    // Check columns
    for (int i = 0; i < board.size(); i++) {
        sum = 0;
        for (int j = 0; j < board.at(0).size(); j++) {
            sum += board.at(j).at(i);
        }
        if (sum == 5) {
            return true;
        }
    }

    return false;
}

vector<vector<vector<int>>> registerNumber(vector<vector<vector<int>>> trackers, vector<vector<vector<int>>> boards, int number) {
    for (int i = 0; i < boards.size(); i++) {
        for (int j = 0; j < boards.at(0).size(); j++) {
            for (int k = 0; k < boards.at(0).at(0).size(); k++) {
                if (boards.at(i).at(j).at(k) == number) {
                    trackers.at(i).at(j).at(k) = 1;
                }
            }
        }
    }
    return trackers;
}

int calculateScore(vector<vector<int>> tracker, vector<vector<int>> board, int winner) {
    int sum = 0;
    for (int j = 0; j < board.size(); j++) {
        for (int k = 0; k < board.at(0).size(); k++) {
            if (tracker.at(j).at(k) == 0) {
                sum += board.at(j).at(k);
            }
        }
    }
    return sum * winner;
}

vector<vector<int>> modifyTracker(vector<vector<int>> tracker) {
    //tracker.at(0) = {1, 1, 1, 1, 1};
    tracker.at(0) = {1, 0, 0, 0, 0};
    tracker.at(1) = {1, 0, 0, 0, 0};
    tracker.at(2) = {1, 0, 0, 0, 0};
    tracker.at(3) = {1, 0, 0, 0, 0};
    tracker.at(4) = {1, 0, 0, 0, 0};
    return tracker;
}

void printRow(vector<int> arr) {
    for (int i = 0; i < arr.size(); i++) {
        cout << arr.at(i) << ' ';
    }
    cout << '\n';
}

void printBoard(vector<vector<int>> board) {
    for (int i = 0; i < board.size(); i++) {
        printRow(board.at(i));
    }
    cout << '\n';
}

void printBoards(vector<vector<vector<int>>> boards) {
    for (int i = 0; i < boards.size(); i++) {
        printBoard(boards.at(i));
    }
}

int main() {
    int boardsize = 5;
    ifstream input("input.txt");
    string line;
    vector<int> numbers;
    vector<vector<int>> board;
    vector<vector<vector<int>>> boards;
    vector<vector<int>> tracker;
    vector<vector<vector<int>>> trackers;
    
    getline(input, line);
    numbers = readNumbers(line, ',');
    //printRow(numbers);

    while (getline(input, line)) {
        boards.push_back(readBoard(&input, boardsize));
    }
    //printBoards(boards);

    trackers = initBoards(boards.size(), boardsize);
    //printBoards(trackers);

    int k = 0;
    int numboards = boards.size();
    int i;
    while (numboards > 1) {
        i = 0;
        trackers = registerNumber(trackers, boards, numbers.at(k));
        while (i < numboards) {
            if (checkBingo(trackers.at(i))) {
                trackers.erase(trackers.begin() + i);
                boards.erase(boards.begin() + i);
                i--;
            }
            numboards = boards.size();
            i++;
        }
        k++;
    }
    while (true) {
        trackers = registerNumber(trackers, boards, numbers.at(k));
        printBoard(trackers.at(0));
        if(checkBingo(trackers.at(0))) {
            break;
        } else {
            k++;
        }
    }
    cout << k << '\n';
    cout << to_string(calculateScore(trackers.at(0), boards.at(0), numbers.at(k))) << '\n';
}