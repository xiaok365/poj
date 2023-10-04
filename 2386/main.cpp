#include <iostream>

using namespace std;

const int dir_x[8] = {0, 0, 1, -1, 1, -1, 1, -1};
const int dir_y[8] = {1, -1, 0, 0, 1, 1, -1, -1};

#define MAX_M 101
#define MAX_N 101
#define QUEUE_LENGTH 10001

struct Node {
    int x, y;

    Node() : x(0), y(0) {}

    Node(int xx, int yy) : x(xx), y(yy) {}
};

int n, m;
char map[MAX_M][MAX_N];
bool visit[MAX_M][MAX_N] = {false};

bool valid(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m && !visit[x][y] && map[x][y] == 'W';
}

void bfs(Node &start) {
    Node queue[QUEUE_LENGTH];
    int head = 0, tail = 1;
    queue[0] = Node(start.x, start.y);
    visit[start.x][start.y] = 0;

    while (head != tail) {
        int x = queue[head].x;
        int y = queue[head].y;

        head = (head + 1) % QUEUE_LENGTH;
        for (int i = 0; i < 8; ++i) {
            int dx = x + dir_x[i];
            int dy = y + dir_y[i];
            if (valid(dx, dy)) {
                visit[dx][dy] = true;
                queue[tail] = Node(dx, dy);
                tail = (tail + 1) % (QUEUE_LENGTH);
            }
        }
    }
}

int main() {

    freopen("../a.in", "r", stdin);

    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; ++i) scanf("%s", map[i]);

    int ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (!visit[i][j] && map[i][j] == 'W') {
                Node start(i, j);
                bfs(start);
                ans++;
            }
        }
    }

    printf("%d", ans);

    return 0;
}
