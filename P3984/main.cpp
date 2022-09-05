#include <iostream>

using namespace std;

#define  MAX_N 5
#define QUEUE_LENGTH 25

struct Node {
    int x, y, d;

    Node() : x(0), y(0), d(0) {}

    Node(int x, int y, int d) : x(x), y(y), d(d) {}
};

const int dir_x[4] = {1, -1, 0, 0};
const int dir_y[4] = {0, 0, 1, -1};

int n, m, map[MAX_N][MAX_N], visit[MAX_N][MAX_N];

bool valid(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m && !map[x][y] && visit[x][y] == -1;
}

void bfs(Node &start, Node &target) {
    Node queue[QUEUE_LENGTH];
    int head = 0, tail = 1;

    memset(visit, 0xff, sizeof visit);
    queue[0] = Node(start.x, start.y, 0);
    visit[start.x][start.y] = 0;

    while (head != tail) {
        int x = queue[head].x;
        int y = queue[head].y;
        int distance = queue[head].d;
        head = (head + 1) % QUEUE_LENGTH;
        for (int i = 0; i < 4; ++i) {
            int dx = x + dir_x[i];
            int dy = y + dir_y[i];
            if (valid(dx, dy)) {
                // 表示从i方向走过来的，方便后续回溯路径
                visit[dx][dy] = i;

                if (dx == target.x && dy == target.y) return;

                // 新坐标入队
                queue[tail] = Node(dx, dy, distance + 1);
                tail = (tail + 1) % (QUEUE_LENGTH);
            }
        }
    }
}

void display(Node &start, Node &target) {

    int path[MAX_N * MAX_N], step = 0;
    int x = target.x, y = target.y;

    if (visit[x][y] == -1) {
        printf("no solution\n");
        return;
    }

    while (!(x == start.x && y == start.y)) {
        int d = visit[x][y];
        path[step++] = d;
        x -= dir_x[d];
        y -= dir_y[d];
    }

    x = 0, y = 0;
    printf("(%d, %d)\n", x, y);
    for (int i = step - 1; i >= 0; --i) {
        x += dir_x[path[i]];
        y += dir_y[path[i]];
        printf("(%d, %d)\n", x, y);
    }
}

int main() {

    freopen("../a.in", "r", stdin);

    int d;
    n = m = 5;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            scanf("%d", &d);
            map[i][j] = d;
        }
    }

    Node start(0, 0, 0), end(4, 4, 0);
    bfs(start, end);
    display(start, end);

    return 0;
}
