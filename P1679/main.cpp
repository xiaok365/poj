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

int find_father(int s) {
    int root = s;
    while (father[root] >= 0) {
        root = father[root];
    }
    while (s != root) {
        int temp = father[s];
        father[s] = root;
        s = temp;
    }
    return root;
}

void union_set(int s, int e) {
    int rootS = find_father(s);
    int rootE = find_father(e);
    if (rootS == rootE) return;
    int weight = father[rootS] + father[rootE];
    if (father[rootS] > father[rootE]) {
        father[rootS] = rootE;
        father[rootE] = weight;
    } else {
        father[rootE] = rootS;
        father[rootS] = weight;
    }
}

int main() {
    freopen("../a.in", "r", stdin);
    int t;
    scanf("%d", &t);
    while (t--) {
        init();
        int ans = 0, i = 0, tail = -1, can = 0, real = 0;
        bool unique = true;
        while (i < m) {
            if (i == tail + 1) {
                can = real = 0;
                for (int j = i; j <= m; ++j) {
                    if (edge[j].value != edge[i].value) {
                        tail = j - 1;
                        break;
                    }
                    if (find_father(edge[j].from) != find_father(edge[j].to)) can++;
                }
            }
            if (find_father(edge[i].from) != find_father(edge[i].to)) {
                union_set(edge[i].from, edge[i].to);
                ans += edge[i].value;
                real++;
            }
            if (i == tail && can != real) {
                unique = false;
                break;
            }
            i++;
        }
        if (!unique) printf("Not Unique!\n"); else printf("%d\n", ans);
    }
    return 0;
}
