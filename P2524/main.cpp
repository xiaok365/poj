#include <iostream>

#define MAX_N 50001
int father[MAX_N];

int find_father(int s) {
    int root = s, temp;
    // 查找s的最顶层根
    while (father[root] >= 0) {
        root = father[root];
    }

    // 路径压缩，提高后续查找效率
    while (s != root) {
        temp = father[s];
        father[s] = root;
        s = temp;
    }
    return root;
}

void union_set(int s, int e) {

    int root_s = find_father(s);
    int root_e = find_father(e);

    if (root_s == root_e) return;
    int weight = father[root_s] + father[root_e];
    // 将结点数少的集合作为结点数多的集合的儿子节点
    if (father[root_s] > father[root_e]) {
        father[root_s] = root_e;
        father[root_e] = weight;
    } else {
        father[root_e] = root_s;
        father[root_s] = weight;
    }
}

int main() {

    freopen("../a.in", "r", stdin);

    int n, m, c = 1, a, b;
    while (scanf("%d %d", &n, &m) && !(n == 0 && m == 0)) {

        memset(father, 0xff, sizeof father);
        for (int i = 0; i < m; ++i) {
            scanf("%d %d", &a, &b);
            union_set(a, b);
        }

        int ans = 0;
        bool flag[MAX_N] = {false};
        for (int i = 1; i <= n; ++i) {
            int f = find_father(i);
            if (!flag[f]) {
                flag[f] = true;
                ans++;
            }
        }

        printf("Case %d: %d\n", c++, ans);
    }
    return 0;
}
