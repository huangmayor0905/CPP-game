#include <bits/stdc++.h>
#define ouo ios_base::sync_with_stdio(false), cin.tie(0)
#define ll long long
#define db double
#define pii pair<int, int>
#define pdd pair<double, double>
using namespace std;

struct history {
    int t;
    int mode;
    ll date;
};

struct timeFormater {
    int y;
    int m;
    int d;
    int hour;
    int min;
    int sec;
};

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
int dir[8][2] = {
    {-1, -1},
    {-1, 0},
    {-1, 1},
    {0, -1},
    {0, 1},
    {1, -1},
    {1, 0},
    {1, 1}};

int r = 8;
int c = 8;
int cntMine = 10;
char mode = 'c';  // 'c', 'p'

bool cmp(history a, history b) {
    if (a.mode == b.mode) return a.t < b.t;
    return a.mode < b.mode;
}

void clearScreen();
void printMenu();
void difficalty();
void eazyMode(int row, int col, int mine, int mode);
void writeFile(int st, int et, int m);
void showHistory();
void printArray(vector<vector<char>> arr);

int main() {
    srand(time(NULL));

    while (true) {
        printMenu();

        int option;
        cin >> option;
        if (option == 1) {
            difficalty();
        } else if (option == 2) {
            showHistory();
        } else if (option == 3) {
            break;
        }
    }
}

void clearScreen() {
    system("cls");
}

void printMenu() {
    clearScreen();
    cout << "\n\n\n"
         << "    1. Play    " << '\n'
         << "   2. History  " << '\n'
         << "    3. Exit    " << '\n'
         << "\n\n\n";
}

void difficalty() {
    clearScreen();
    cout << "\n\n\n"
         << "     1. Eazy     " << '\n'
         << "    2. Normal    " << '\n'
         << "     3. Hard     " << '\n'
         << "\n\n\n";
    int option;
    cin >> option;

    if (option == 1) {
        eazyMode(8, 8, 10, 1);
    } else if (option == 2) {
        eazyMode(16, 16, 40, 2);
    } else if (option == 3) {
        eazyMode(16, 30, 99, 3);
    }
}

void eazyMode(int row, int col, int mine, int mode) {
    // init
    clearScreen();

    r = row;
    c = col;
    cntMine = mine;

    vector<vector<int>> grid;
    vector<vector<char>> gameMap;
    for (int i = 0; i < r; i++) {
        grid.push_back({});
        gameMap.push_back({});
        for (int j = 0; j < c; j++) {
            grid[i].push_back(0);
            gameMap[i].push_back('#');
        }
    }
    set<pair<int, int>> Mine;
    while (Mine.size() != cntMine) {
        int x = rand() % r;
        int y = rand() % c;
        if (Mine.find({x, y}) == Mine.end()) {
            Mine.insert({x, y});
            grid[x][y] = 1;
        }
    }

    int x, y;
    int cntUnopened = r * c - cntMine;
    time_t startTime = time(0);

    while (cntUnopened != 0) {
        clearScreen();
        printArray(gameMap);
        // cout << "[c] Open [p] Mark ";
        // cin >> mode;
        cout << "Input the coordinate (e.g. 3 5): ";
        cin >> x >> y;
        if (x < 1 || x > r || y < 1 || y > c) {
            cout << "超過範圍，請重新輸入\n";
            system("pause");
            continue;
        }

        // if (mode == 'p') {
        //     if (gameMap[x - 1][y - 1] == 'p') {
        //         gameMap[x - 1][y - 1] = '#';
        //     } else if (gameMap[x - 1][y - 1] == '#') {
        //         gameMap[x - 1][y - 1] = 'p';
        //     }
        //     continue;
        // } else if (mode == 'c') {
        queue<pair<int, int>> que;
        que.push({x - 1, y - 1});
        while (!que.empty()) {
            auto now = que.front();
            que.pop();

            if (grid[now.first][now.second] == 1) {
                cout << "BOOM!\n";
                system("pause");
                return;
            }
            if (grid[now.first][now.second] == -1) continue;

            grid[now.first][now.second] = -1;
            cntUnopened--;

            // check for mine;
            int cntNearMine = 0;
            for (int k = 0; k < 8; k++) {
                int nx = now.first + dir[k][0];
                int ny = now.second + dir[k][1];

                if (nx >= 0 && nx < r && ny >= 0 && ny < c) {
                    if (grid[nx][ny] == 1) cntNearMine++;
                }
            }
            if (cntNearMine != 0) {
                gameMap[now.first][now.second] = '0' + cntNearMine;
                continue;
            } else {
                gameMap[now.first][now.second] = '_';
            }
            for (int k = 0; k < 8; k++) {
                int nx = now.first + dir[k][0];
                int ny = now.second + dir[k][1];
                if (nx >= 0 && nx < r && ny >= 0 && ny < c) {
                    if (grid[nx][ny] == 0) {
                        que.push({nx, ny});
                    }
                }
            }
        }
        // }
    }
    time_t endTime = time(0);
    writeFile(startTime, endTime, mode);

    // printArray(gameMap);
    cout << "You win!\n";
    system("pause");
}

void writeFile(int st, int et, int m) {
    ofstream out;
    out.open("history.txt", ios::app);
    if (out.fail()) {
        cout << "output file opening failed\n";
        return;
    }
    out << et - st << ' ' << st << ' ' << m << endl;
    out.close();
}

void showHistory() {
    clearScreen();
    ifstream in;
    in.open("history.txt");
    if (in.fail()) {
        cout << "input file opening failed\n";
        return;
    }
    string str;
    vector<history> rank;
    history tmp;
    while (in >> tmp.t >> tmp.date >> tmp.mode) {
        rank.push_back(tmp);
    }
    sort(rank.begin(), rank.end(), cmp);
    for (int i = 0; i < rank.size(); i++) {
        // mode
        switch (rank[i].mode) {
            case 1:
                cout << " 模式：簡單 \n";
                break;
            case 2:
                cout << " 模式：普通 \n";
                break;
            case 3:
                cout << " 模式：困難 \n";
                break;
            default:
                break;
        }

        cout << " 耗時：" << rank[i].t << '\n';

        // date
        time_t gameTime = rank[i].date;
        tm* t = localtime(&gameTime);
        cout << " 時間：";
        cout << t->tm_year + 1900 << '/'
             << t->tm_mon + 1 << '/'
             << t->tm_mday << ' '
             << t->tm_hour << ':'
             << t->tm_min << ':'
             << t->tm_sec << '\n';

        cout << "------------------------------\n";
    }
    in.close();
    system("pause");
}

void printArray(vector<vector<char>> arr) {
    cout << "  ";
    for (int j = 0; j < arr[0].size(); j++) cout << (j + 1) % 10 << ' ';
    cout << '\n';
    for (int i = 0; i < arr.size(); i++) {
        cout << (i + 1) % 10 << ' ';
        // if (i + 1 < 10) cout << ' ';
        for (int j = 0; j < arr[i].size(); j++) {
            cout << arr[i][j] << ' ';
        }
        cout << '\n';
    }
}
