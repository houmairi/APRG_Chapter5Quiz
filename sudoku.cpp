#include <iostream>
#include <string>
using namespace std;

class Sudoku {
private:
    int board[82];
    
    bool isValid(int pos, int num) {
        int row = pos / 9;
        int col = pos % 9;
        
        // Check row
        for (int i = 0; i < 9; i++) {
            if (board[row * 9 + i] == num) return false;
        }
        
        // Check column
        for (int i = 0; i < 9; i++) {
            if (board[i * 9 + col] == num) return false;
        }
        
        // Check 3x3 box
        int boxRow = row - row % 3;
        int boxCol = col - col % 3;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[(boxRow + i) * 9 + (boxCol + j)] == num) return false;
            }
        }
        
        return true;
    }
    
    int findEmptyCell() {
        int bestPos = -1;
        int minPossibilities = 10;
        
        for (int pos = 0; pos < 81; pos++) {
            if (board[pos] == 0) {
                int count = 0;
                for (int num = 1; num <= 9; num++) {
                    if (isValid(pos, num)) count++;
                }
                if (count < minPossibilities) {
                    minPossibilities = count;
                    bestPos = pos;
                    if (count == 1) break;  // Optimization: cell with only one possibility
                }
            }
        }
        
        return bestPos;
    }
    
    bool solveCSP() {
        int pos = findEmptyCell();
        if (pos == -1) return true;  // No empty cells left
        
        for (int num = 1; num <= 9; num++) {
            if (isValid(pos, num)) {
                board[pos] = num;
                if (solveCSP()) return true;
                board[pos] = 0;  // backtrack
            }
        }
        
        return false;
    }

public:
    Sudoku(string s) {
        for (unsigned int i = 0; i < s.length(); i++) {
            board[i] = (int)(s[i] - '0');
        }
    }
    
    void solve() {
        if (solveCSP()) {
            cout << "done!" << endl;
            for (int i = 0; i < 9; i++) {
                for (int j = 0; j < 9; j++) {
                    cout << board[i * 9 + j];
                    if (j < 8) cout << " ";
                    if (j == 2 || j == 5) cout << "| ";
                }
                cout << endl;
                if (i == 2 || i == 5) {
                    cout << "------+-------+------" << endl;
                }
            }
        } else {
            cout << "no solution" << endl;
        }
    }
};

int main() {
    char str[82];
    cin >> str;
    Sudoku solver(str);
    solver.solve();
    return 0;
}