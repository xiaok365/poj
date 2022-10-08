#include <iostream>
#include <algorithm>

using namespace std;

#define MAX_N 101

struct Edge {
    int from, to, value;

    bool operator<(const Edge &other) const {
        return value < other.value;
    }
};

Edge edge[MAX_N * MAX_N];
int n, m, father[MAX_N];

void init() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; ++i) {
        scanf("%d %d %d", &edge[i].from, &edge[i].to, &edge[i].value);
    }
    sort(edge, edge + m);
    memset(father, 0xff, sizeof father);
}

int find(int x) {
    int root = x;
    while (father[root] >= 0) {
        root = father[root];
    }
    while (x != root) {
        int t = father[x];
        father[x] = root;
        x = t;
    }
    return root;
}

void unite(int a, int b) {
    int fa = find(a), fb = find(b);
    if (fa == fb) return;
    int weight = father[fa] + father[fb];
    if (father[fa] > father[fb]) {
        father[fa] = fb, father[fb] = weight;
    } else {
        father[fb] = fa, father[fa] = weight;
    }
}

int main() {
    freopen("../a.in", "r", stdin);
    int t;
    scanf("%d", &t);
    while (t--) {
        init();
        int ans = 0, i = 0, tail = -1, possible = 0, actual = 0;
        bool unique = true;
        while (i < m) {
            if (i == tail + 1) {
                possible = actual = 0;
                for (int j = i; j <= m; ++j) {
                    if (edge[j].value != edge[i].value) {
                        tail = j - 1;
                        break;
                    }
                    if (find(edge[j].from) != find(edge[j].to)) possible++;
                }
            }
            if (find(edge[i].from) != find(edge[i].to)) {
                unite(edge[i].from, edge[i].to);
                ans += edge[i].value;
                actual++;
            }
            if (i == tail && possible != actual) {
                unique = false;
                break;
            }
            i++;
        }
        if (!unique) printf("Not Unique!\n"); else printf("%d\n", ans);
    }
    return 0;
}
