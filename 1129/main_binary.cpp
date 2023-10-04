#include <iostream>

using namespace std;

#define  MAX_N 26
int n, ans, neighbor[MAX_N];

int count_one(int x) {
    int ret = 0;
    while (x) {
        x &= x - 1;
        ret++;
    }
    return ret;
}

void bron_kerbosch(int r, int p, int x) {
    if (p == 0 && x == 0) {
        int t = count_one(r);
        if (t > ans) ans = t;
        return;
    }

    int u = 0;
    while (!((1 << u) & (p | x)) && u < n) u++;

    // 枚举所有点
    for (int v = 0; v < n; ++v) {
        if ((1 << v & p) == 0 || neighbor[u] & 1 << v) continue;
        bron_kerbosch(r | 1 << v, p & neighbor[v], x & neighbor[v]);
        p -= 1 << v;
        x |= 1 << v;
    }
}


int main() {

    freopen("../a.in", "r", stdin);

    char st[MAX_N + 2];

    while (scanf("%d", &n) && n != 0) {
        memset(neighbor, 0, sizeof neighbor);
        for (int i = 0; i < n; ++i) {
            scanf("%s", st);
            for (int j = 2; st[j] != '\0'; ++j) {
                neighbor[st[0] - 'A'] |= 1 << (st[j] - 'A');
                neighbor[st[j] - 'A'] |= 1 << (st[0] - 'A');
            }
        }

        int r, p, x;
        r = p = x = 0;
        for (int i = 0; i < n; ++i) p += 1 << i;
        ans = 0;
        bron_kerbosch(r, p, x);
        if (ans == 1) printf("%d channel needed.\n", ans);
        else printf("%d channels needed.\n", ans);
    }

    return 0;
}
