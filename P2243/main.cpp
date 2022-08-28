#include <iostream>

#define MAX_N 9
#define QUEUE_LENGTH 65

const int dir_x[8] = {-1, -2, -1, -2, 1, 2, 1, 2};
const int dir_y[8] = {2, 1, -2, -1, 2, 1, -2, -1};

struct Node {
    int x, y, distance;

    Node() : x(0), y(0), distance(0) {}

    Node(int xx, int yy) : x(xx), y(yy), distance(0) {}

    Node(int xx, int yy, int d) : x(xx), y(yy), distance(d) {}
};


int n;
bool visit[MAX_N][MAX_N];

bool valid(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < n && !visit[x][y];
}

int bfs(Node &start, Node &target) {
    Node queue[QUEUE_LENGTH];
    int head = 0, tail = 1;
    queue[0] = Node(start.x, start.y);
    visit[start.x][start.y] = true;

    while (head != tail) {
        int x = queue[head].x;
        int y = queue[head].y;
        int distance = queue[head].distance;
        head = (head + 1) % QUEUE_LENGTH;
        for (int i = 0; i < 8; ++i) {
            int dx = x + dir_x[i];
            int dy = y + dir_y[i];
            if (valid(dx, dy)) {
                visit[dx][dy] = true;

                if (dx == target.x && dy == target.y) {
                    return distance + 1;
                }

                // 新坐标入队
                queue[tail] = Node(dx, dy, distance + 1);
                tail = (tail + 1) % (QUEUE_LENGTH);
            }
        }
    }

    return 0;
}

int main() {

    freopen("../a.in", "r", stdin);

    char a[3], b[3];
    n = 8;

    while (~scanf("%s %s", a, b)) {
        memset(visit, false, sizeof visit);
        Node start, target;
        start.x = a[1] - '1', start.y = a[0] - 'a';
        target.x = b[1] - '1', target.y = b[0] - 'a';
        printf("To get from %s to %s takes %d knight moves.\n", a, b, bfs(start, target));
    }
    return 0;
}
