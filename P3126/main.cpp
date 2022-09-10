#include <iostream>

#define MAX_N 10001
#define MAX_M 1229
bool num[MAX_N] = {false};
int prime[MAX_M], cnt = 0;

void get_prime() {
    for (int i = 2; i < MAX_N; i++) {
        if (!num[i]) {
            prime[cnt++] = i;
        }
        for (int j = 0; j < cnt && i * prime[j] < MAX_N; ++j) {
            num[i * prime[j]] = true;
            if (i % prime[j] == 0) break;
        }
    }
}

struct Node {
    int x, d;

    Node() {}

    Node(int x, int d) : x(x), d(d) {}
};

bool visit[MAX_N];

bool valid(int x) {
    return x >= 1000 && !num[x] && !visit[x];
}

int change(int x, int i, int j) {
    switch (i) {
        case 0:
            return j * 1000 + x % 1000;
        case 1:
            return x / 1000 * 1000 + j * 100 + x % 100;
        case 2:
            return x / 100 * 100 + j * 10 + x % 10;
        default:
            return x / 10 * 10 + j;
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
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 10; ++j) {
                int dx = change(x, i, j);
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
    }

    return step;
}

int main() {
    freopen("../a.in", "r", stdin);

    get_prime();

    int t, n, m;
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d", &n, &m);
        printf("%d\n", bfs(n, m));
    }

    return 0;
}
