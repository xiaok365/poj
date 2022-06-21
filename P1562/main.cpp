#include <iostream>
#include <fstream>

using namespace std;

const int MAXN = 100, MAXM = 100;
char map[MAXM][MAXN];
int m, n;
bool visit[MAXM][MAXN];

const int direction[8][2] = {{-1, -1},
                             {-1, 0},
                             {-1, 1},
                             {0,  -1},
                             {0,  1},
                             {1,  -1},
                             {1,  0},
                             {1,  1}};

struct Node {
    int x, y;

    Node() {}

    Node(int xx, int yy) : x(xx), y(yy) {}
};

void init() {
    memset(visit, false, MAXM * MAXN);
}

void bfs(int s, int t) {
    Node queue[MAXN * MAXM];
    int head = 0, tail = 1;
    queue[0] = Node(s, t);
    visit[s][t] = true;
    while (head != tail) {
        int x = queue[head].x;
        int y = queue[head].y;
        head = (head + 1) % (MAXN * MAXM);
        for (int i = 0; i < 8; ++i) {
            int dx = x + direction[i][0];
            int dy = y + direction[i][1];
            if (dx >= 0 && dx < m && dy >= 0 && dy < n && !visit[dx][dy] && map[dx][dy] == '@') {
                visit[dx][dy] = true;
                queue[tail] = Node(dx, dy);
                tail = (tail + 1) % (MAXN * MAXM);
            }
        }
    }
}

int main() {


    ifstream cin("../a.in");
    ofstream cout("../a.out");

    int i, j;

    while (cin >> m >> n && m > 0) {
        init();
        for (i = 0; i < m; ++i) {
            for (j = 0; j < n; ++j) {
                cin >> map[i][j];
            }
        }
        int ans = 0;
        for (i = 0; i < m; ++i) {
            for (j = 0; j < n; ++j) {
                if (!visit[i][j] && map[i][j] == '@') {
                    bfs(i, j);
                    ans++;
                }
            }
        }
        cout << ans << endl;
    }
    return 0;
}