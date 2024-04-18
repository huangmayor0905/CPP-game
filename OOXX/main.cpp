#include <iostream>
#include <vector>
using namespace std;

void printBoard(const vector<vector<char>>& board) {
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            cout << board[i][j] << (j == board[i].size() - 1 ? ' ' : '|');
        }
        cout << ((i == board.size() - 1) ? "\n" : "\n-----");
        cout << "\n";
    }
}

bool checkWin(const vector<vector<char>>& board, char player) {
    // 檢查行和列
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) {
            return true;  // 水平獲勝
        }
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player) {
            return true;  // 垂直獲勝
        }
    }
    // 檢查對角線
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player)) {
        return true;  // 對角線獲勝
    }
    return false;  // 沒有獲勝
}

bool isGameOver(const vector<vector<char>>& board) {
    for (const auto& row : board) {
        for (char cell : row) {
            if (cell == ' ') {
                return false;  // 還有空位，遊戲繼續
            }
        }
    }
    return true;  // 沒有空位，遊戲結束
}

int main() {
    vector<vector<char>> board(3, vector<char>(3, ' '));  // 初始化遊戲板
    char currentPlayer = 'X';                             // 設置當前玩家

    while (true) {
        system("cls");
        cout << "當前棋盤：" << endl;
        printBoard(board);

        int row, col;
        cout << "輪到 " << currentPlayer << " 玩家，請輸入座標（行 列）：";
        cin >> row >> col;

        // 檢查座標的合法性
        if (row < 1 || row > 3 || col < 1 || col > 3 || board[row - 1][col - 1] != ' ') {
            cout << "輸入無效！請重新輸入。" << endl;
            system("pause");
            continue;
        }

        board[row - 1][col - 1] = currentPlayer;

        // 檢查是否有玩家獲勝
        if (checkWin(board, currentPlayer)) {
            cout << "恭喜玩家 " << currentPlayer << " 獲勝！" << endl;
            break;
        }

        // 檢查遊戲是否結束
        if (isGameOver(board)) {
            cout << "遊戲結束，平局！" << endl;
            break;
        }

        // 切換玩家
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    return 0;
}
