#include <iostream>
#include <cstdio>
#include <queue>

using namespace std;

#define MAX_N 51
#define MAX_POINT 101

const int dir[4][2] = {1, 0, -1, 0, 0, 1, 0, -1};

char map[MAX_N][MAX_N];
int num[MAX_N][MAX_N], edge[MAX_POINT][MAX_POINT];
int cnt, n, m;

struct Node {
    int x, y, dis;
    Node(int x, int y, int d) : x(x), y(y), dis(d) {}
};

void init() {

    memset(map, 0, sizeof map);
    memset(num, 0xff, sizeof num);
    memset(edge, 0x3f, sizeof edge);

    cnt = 0;
}

bool valid(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m;
}

void bfs(int start_x, int start_y) {

    queue<Node> my_queue;
    bool visit[MAX_N][MAX_N] = {false};

    visit[start_x][start_y] = true;
    my_queue.push(Node(start_x, start_y, 0));
    int cur_num = num[start_x][start_y];
    edge[cur_num][cur_num] = 0;

    while (!my_queue.empty()) {
        Node cur = my_queue.front();
        my_queue.pop();
        for (int i = 0; i < 4; ++i) {
            int dx = cur.x + dir[i][0];
            int dy = cur.y + dir[i][1];
            if (valid(dx, dy) && !visit[dx][dy] && map[dx][dy] != '#') {
                my_queue.push(Node(dx, dy, cur.dis + 1));
                visit[dx][dy] = true;
                if (num[dx][dy] > 0) {
                    edge[cur_num][num[dx][dy]] = cur.dis + 1;
                    edge[num[dx][dy]][cur_num] = cur.dis + 1;
                }
            }
        }
    }
}

int prim() {
    int ans = 0, dist[MAX_POINT];
    bool visit[MAX_POINT] = {false};
    // 将0作为起点加入集合S
    visit[0] = true;

    // dist初始化
    memset(dist, 0x3f, sizeof dist);
    for (int i = 0; i < cnt; ++i) dist[i] = edge[0][i];

    // 选择N-1条边
    for (int i = 1; i < cnt; ++i) {

        int min = 0x3f3f3f3f, k = -1;
        // 枚举非S所有点，选择最小的边
        for (int j = 1; j < cnt; ++j) {
            if (!visit[j] && dist[j] < min) {
                min = dist[j];
                k = j;
            }
        }

        ans += min;
        // 将新的点k加入集合S,并通过k更新非S中点的距离
        visit[k] = true;
        for (int j = 1; j < cnt; ++j) {
            if (!visit[j] && edge[k][j] < dist[j]) {
                dist[j] = edge[k][j];
            }
        }
    }

    return ans;
}

int main() {

    freopen("../a.in", "r", stdin);

    int t;
    scanf("%d", &t);

    while (t--) {
        init();
        char space[100];
        scanf("%d %d%[^\n]", &m, &n, space);
        getchar();

        for (int i = 0; i < n; ++i) {
            scanf("%[^\n]", map[i]);
            getchar();
        }

        // 标号
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (map[i][j] == 'S' || map[i][j] == 'A') {
                    num[i][j] = cnt++;
                }
            }
        }

        // 求距离
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (num[i][j] >= 0) {
                    bfs(i, j);
                }
            }
        }

        printf("%d\n", prim());
    }
    return 0;
}
