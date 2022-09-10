#include <iostream>

#define MAX_N 100001

struct Node {
    int x, d;

    Node() {}

    Node(int x, int d) : x(x), d(d) {}
};

bool visit[MAX_N];

bool valid(int x) {
    return x >= 0 && x <= 100000 && !visit[x];
}

int move(int i, int x) {
    switch (i) {
        case 0:
            return x - 1;
        case 1:
            return x + 1;
        default:
            return 2 * x;
    }
}

int bfs(int n, int m) {
    Node queue[MAX_N];
    int head = 0, tail = 1, step = 0;

    memset(visit, false, sizeof visit);
    queue[0] = Node(n, 0);
    visit[n] = true;

    while (head != tail) {
        int x = queue[head].x;
        int d = queue[head].d;
        head = (head + 1) % MAX_N;
        for (int i = 0; i < 3; ++i) {
            int dx = move(i, x);
            if (valid(dx)) {
                visit[dx] = true;
                if (dx == m) {
                    step = d + 1;
                    break;
                }
                queue[tail] = Node(dx, d + 1);
                tail = (tail + 1) % (MAX_N);
            }
        }
    }

    return step;
}

int main() {
    freopen("../a.in", "r", stdin);

    int n, m;
    scanf("%d %d", &n, &m);
    printf("%d", bfs(n, m));

    return 0;
}
