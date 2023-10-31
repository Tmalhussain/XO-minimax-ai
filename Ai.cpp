#include <iostream>
using namespace std;

char board[3][3] = { { '_', '_', '_' }, { '_', '_', '_' }, { '_', '_', '_' } };
struct Move { int row, col; };
struct triple { int win = 0, loss = 0, tie = 0; };

int inf = 1000000007;
char hu = 'X', ai = 'O';

// Function to check if there are any empty spots on the board
bool movesleft(char a[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (a[i][j] == '_') return true;
        }
    }
    return false;
}

// Evaluate the current state of the board
int eval(char a[3][3]) {
    // Check rows and columns for a win
    for (int i = 0; i < 3; i++) {
        if ((a[i][0] == a[i][1] && a[i][1] == a[i][2] && a[i][0] != '_') ||
            (a[0][i] == a[1][i] && a[1][i] == a[2][i] && a[0][i] != '_')) {
            return (a[i][0] == ai) ? 10 : -10;
        }
    }
    // Check diagonals for a win
    if (a[0][0] == a[1][1] && a[1][1] == a[2][2] && a[0][0] != '_') {
        return (a[0][0] == ai) ? 10 : -10;
    }
    if (a[0][2] == a[1][1] && a[1][1] == a[2][0] && a[0][2] != '_') {
        return (a[0][2] == ai) ? 10 : -10;
    }
    return 0;
}

// Minimax algorithm to find the optimal move
triple minimax(char b[3][3], bool isMax, triple t) {
    int score = eval(b);
    if (score == 10 || score == -10) return t + score;
    if (!movesleft(b)) {
        t.tie++;
        return t;
    }

    if (isMax) {
        int best = -inf;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (b[i][j] == '_') {
                    b[i][j] = ai;
                    t = minimax(b, !isMax, t);
                    b[i][j] = '_';
                }
            }
        }
        return t;
    } else {
        int best = inf;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (b[i][j] == '_') {
                    b[i][j] = hu;
                    t = minimax(b, !isMax, t);
                    b[i][j] = '_';
                }
            }
        }
        return t;
    }
}

// Find the best move for AI
Move find_best(char b[3][3]) {
    int best = -inf;
    Move bestMove = {-1, -1};
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (b[i][j] == '_') {
                b[i][j] = ai;
                triple moveEval = minimax(b, false, {0, 0, 0});
                b[i][j] = '_';
                if (moveEval.win - moveEval.loss > best) {
                    bestMove = {i, j};
                    best = moveEval.win - moveEval.loss;
                }
            }
        }
    }
    cout << "AI Move Value: " << best << endl;
    return bestMove;
}

// Display the current state of the board
void display(char b[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << b[i][j] << ((j == 2) ? '\n' : ' | ');
        }
        if (i < 2) cout << "---------\n";
    }
}

int main() {
    while (true) {
        cout << "Current Board:\n";
        display(board);
        cout << "Your Move (row col): ";
        int row, col;
        cin >> row >> col;
        row--; col--;
        if (board[row][col] == '_') {
            board[row][col] = hu;
        } else {
            cout << "Invalid Move!\n";
            continue;
        }

        if (eval(board) == -10) {
            cout << "You Win!\n";
            break;
        }
        if (!movesleft(board)) {
            cout << "It's a Tie!\n";
            break;
        }

        cout << "AI Move...\n";
        Move bestMove = find_best(board);
        board[bestMove.row][bestMove.col] = ai;
        if (eval(board) == 10) {
            display(board);
            cout << "AI Wins!\n";
            break;
        }
        if (!movesleft(board)) {
            cout << "It's a Tie!\n";
            break;
        }
    }
    return 0;
}
