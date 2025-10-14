#include <iostream>
#include <vector>
#include <limits>
using namespace std;

const int HUMAN = -1; // X
const int AI = 1;     // O

void printBoard(vector<vector<char>>& board) {
    cout << "\n";
    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) {
            cout << (board[i][j]==' ' ? '.' : board[i][j]) << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

bool movesLeft(vector<vector<char>>& board) {
    for (int i=0; i<3; i++)
        for (int j=0; j<3; j++)
            if (board[i][j] == ' ') return true;
    return false;
}

int evaluate(vector<vector<char>>& b) {
    // Rows
    for (int row=0; row<3; row++) {
        if (b[row][0]==b[row][1] && b[row][1]==b[row][2]) {
            if (b[row][0]=='O') return +10;
            else if (b[row][0]=='X') return -10;
        }
    }
    // Cols
    for (int col=0; col<3; col++) {
        if (b[0][col]==b[1][col] && b[1][col]==b[2][col]) {
            if (b[0][col]=='O') return +10;
            else if (b[0][col]=='X') return -10;
        }
    }
    // Diagonals
    if (b[0][0]==b[1][1] && b[1][1]==b[2][2]) {
        if (b[0][0]=='O') return +10;
        else if (b[0][0]=='X') return -10;
    }
    if (b[0][2]==b[1][1] && b[1][1]==b[2][0]) {
        if (b[0][2]=='O') return +10;
        else if (b[0][2]=='X') return -10;
    }
    return 0;
}

// Minimax function
int minimax(vector<vector<char>>& board, int depth, bool isMax) {
    int score = evaluate(board);

    if (score == 10) return score - depth;  // prefer quicker win
    if (score == -10) return score + depth; // prefer slower loss
    if (!movesLeft(board)) return 0;        // draw

    if (isMax) { // AI's turn (O)
        int best = numeric_limits<int>::min();
        for (int i=0; i<3; i++) {
            for (int j=0; j<3; j++) {
                if (board[i][j]==' ') {
                    board[i][j] = 'O';
                    best = max(best, minimax(board, depth+1, false));
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    } else { // Human's turn (X)
        int best = numeric_limits<int>::max();
        for (int i=0; i<3; i++) {
            for (int j=0; j<3; j++) {
                if (board[i][j]==' ') {
                    board[i][j] = 'X';
                    best = min(best, minimax(board, depth+1, true));
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    }
}

// Find best move for AI
pair<int,int> findBestMove(vector<vector<char>>& board) {
    int bestVal = numeric_limits<int>::min();
    pair<int,int> bestMove = {-1,-1};

    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) {
            if (board[i][j]==' ') {
                board[i][j] = 'O';
                int moveVal = minimax(board, 0, false);
                board[i][j] = ' ';
                if (moveVal > bestVal) {
                    bestMove = {i,j};
                    bestVal = moveVal;
                }
            }
        }
    }
    return bestMove;
}

int main() {
    vector<vector<char>> board(3, vector<char>(3, ' '));
    cout << "Tic-Tac-Toe with Minimax\nYou are X, Computer is O\n";

    while (true) {
        printBoard(board);
        if (!movesLeft(board) || evaluate(board)!=0) break;

        // Human move
        int r,c;
        cout << "Enter your move (row col 0-2): ";
        cin >> r >> c;
        if (r<0||r>2||c<0||c>2||board[r][c]!=' ') {
            cout << "Invalid move. Try again.\n";
            continue;
        }
        board[r][c] = 'X';

        if (!movesLeft(board) || evaluate(board)!=0) break;

        // AI move
        pair<int,int> best = findBestMove(board);
        board[best.first][best.second] = 'O';
        cout << "Computer chose: " << best.first << " " << best.second << "\n";
    }

    printBoard(board);
    int score = evaluate(board);
    if (score == 10) cout << "Computer wins!\n";
    else if (score == -10) cout << "You win!\n";
    else cout << "It's a draw!\n";

    return 0;
}
