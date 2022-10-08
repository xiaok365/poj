#include <iostream>

#define MAX_N 100001

int father[MAX_N * 2];

int find(int s) {
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

void unite(int s, int e) {
    int fs = find(s);
    int fe = find(e);
    if (fs == fe) return;
    if (father[fs] > father[fe]) {
        father[fe] = father[fs] + father[fe];
        father[fs] = fe;
    } else {
        father[fs] = father[fs] + father[fe];
        father[fe] = fs;
    }
}

void query(int n, int a, int b) {
    if (find(a) == find(b)) {
        printf("In the same gang.\n");
    } else if (find(a) == find(b + n)) {
        printf("In different gangs.\n");
    } else {
        printf("Not sure yet.\n");
    }
}

int main() {
    freopen("../a.in", "r", stdin);
    int t, n, m;
    scanf("%d", &t);
    while (t--) {
        memset(father, 0xff, sizeof father);
        scanf("%d %d", &n, &m);
        for (int i = 0; i < m; ++i) {
            char ch[2];
            int a, b;
            scanf("%s %d %d", ch, &a, &b);
            switch (ch[0]) {
                case 'D':
                    unite(a, b + n);
                    unite(b, a + n);
                    break;
                default:
                    query(n, a, b);
            }
        }
    }

    return 0;
}
