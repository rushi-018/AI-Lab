#include <iostream>
#include <vector>
using namespace std;

const int N = 8;

// Function to print the chessboard
void printBoard(vector<int>& board) {
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            if (board[i] == j) cout << "Q ";
            else cout << ". ";
        }
        cout << "\n";
    }
    cout << "\n";
}

// Check if queen can be placed at row, col
bool isSafe(vector<int>& board, int row, int col) {
    for (int i=0; i<row; i++) {
        int qCol = board[i];
        if (qCol == col || abs(qCol - col) == abs(i - row))
            return false;
    }
    return true;
}

// Backtracking to place queens
bool solveNQueens(vector<int>& board, int row) {
    if (row == N) {
        printBoard(board);
        return true; // found one solution
    }

    for (int col=0; col<N; col++) {
        if (isSafe(board, row, col)) {
            board[row] = col;
            if (solveNQueens(board, row+1)) return true;
        }
    }
    return false;
}

int main() {
    vector<int> board(N, -1);

    cout << "Solving 8 Queens Problem using Backtracking...\n\n";
    if (!solveNQueens(board, 0)) {
        cout << "No solution found.\n";
    }

    return 0;
}
