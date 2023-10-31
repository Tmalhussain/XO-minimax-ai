#include <iostream>
using namespace std;

char board[3][3] = { { '_', '_', '_' }, { '_', '_', '_' }, { '_', '_', '_' } };
struct Move { int row, col; };
struct triple { int win = 0, loss = 0, tie = 0; };

int inf = 1000000007;
char hu = 'X', ai = 'O';
bool movesleft(char a[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (a[i][j] == '_') return true;
        }
    }
    return false;
}

int eval(char a[3][3]) {
    for (int i = 0; i < 3; i++) {
        if (a[i][0] == a[i][1] && a[i][1] == a[i][2] && a[i][1] != '_') {
            if (a[i][0] == ai) return 10;
            else return -10;
        }
    }
    for (int i = 0; i < 3; i++) {
        if (a[0][i] == a[1][i] && a[1][i] == a[2][i] && a[2][i] != '_') {
            if (a[0][i] == ai) return 10;
            else return -10;
        }
    }
    if (a[0][0] == a[1][1] && a[1][1] == a[2][2] && a[2][2] != '_') {
        if (a[0][0] == hu) return -10;
        else if (a[0][0] == ai) return 10;
    }

    if (a[0][2] == a[1][1] && a[1][1] == a[2][0] && a[1][1] != '_') {
        if (a[0][2] == ai) return 10;
        else if (a[0][2] == hu) return -10;
    }
    return 0;
}
int minimax(char b[3][3], bool isMax) {
    int score = eval(b);
    if (score == 10) return score;
    if (score == -10) return score;
    if (!movesleft(b)) return 0;

    if (isMax) {
        int best = INT_MIN;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (b[i][j] == '_') {
                    b[i][j] = ai;
                    best = max(best, minimax(b, !isMax));
                    b[i][j] = '_';
                }
            }
        }
        return best;
    } else {
        int best = INT_MAX;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (b[i][j] == '_') {
                    b[i][j] = hu;
                    best = min(best, minimax(b, !isMax));
                    b[i][j] = '_';
                }
            }
        }
        return best;
    }
}

Move find_best(char b[3][3]) {
    int best = INT_MIN;
    Move bestMove = {-1, -1};

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (b[i][j] == '_') {
                b[i][j] = ai;
                int moveVal = minimax(b, false);
                b[i][j] = '_';

                if (moveVal > best) {
                    bestMove.row = i;
                    bestMove.col = j;
                    best = moveVal;
                }
            }
        }
    }

    if (bestMove.row == -1 || bestMove.col == -1) {
        cout << "AI couldn't find a valid move!" << endl;
        exit(EXIT_FAILURE);
    }
    cout << "The value of the best Move is : " << best << endl << endl;
    return bestMove;
}

void display(char b[3][3]){
    cout<<b[0][0]<<" | "<<b[0][1]<<" | "<<b[0][2]<<"\n---------\n"<<b[1][0]<<" | "<<b[1][1]<< " | " <<b[1][2]<<"\n---------\n"<<b[2][0]<< " | "<<b[2][1]<< " | " <<b[2][2];
}
int main() {
    int playerRow, playerCol;
    while (true) {
        cout << "Current Board: " << endl;
        display(board);
        cout << "\nYour Move (Enter row and column separated by space): ";
        cin >> playerRow >> playerCol;
        playerRow--;playerCol--;
        if (board[playerRow][playerCol] == '_') {
            board[playerRow][playerCol] = hu;
        } else {
            cout << "Invalid Move! Try again." << endl;
            continue;
        }

        // Check if player wins
        if (eval(board) == -10) {
            cout << "You Win!" << endl;
            break;
        }

        // Check for a tie
        if (!movesleft(board)) {
            cout << "It's a Tie!" << endl;
            break;
        }

        // AI's Move
        cout << "AI is making a move..." << endl;
        Move bestMove = find_best(board);
        board[bestMove.row][bestMove.col] = ai;
        display(board);

        // Check if AI wins
        if (eval(board) == 10) {
            cout << "AI Wins! Better luck next time." << endl;
            break;
        }

        // Check for a tie again
        if (!movesleft(board)) {
            cout << "It's a Tie!" << endl;
            break;
        }
    }

    return 0;
}
