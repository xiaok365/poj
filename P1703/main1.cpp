#include <iostream>

#define MAX_N 100001

int father[MAX_N], relation[MAX_N], stack[MAX_N];

int find(int s) {
    int root = s, cnt = 0;
    while (father[root] >= 0) {
        stack[cnt++] = root;
        root = father[root];
    }
    for (int i = cnt - 2; i >= 0; --i) {
        father[stack[i]] = root;
        relation[stack[i]] = (relation[stack[i]] + relation[stack[i + 1]]) % 2;
    }
    return root;
}

void join(int a, int b, int fa, int fb) {
    father[fb] = father[fa] + father[fb];
    father[fa] = fb;
    int a2fb = 1 + relation[b];
    relation[fa] = (a2fb - relation[a] + 2) % 2;
}

void unite(int a, int b) {
    int fa = find(a);
    int fb = find(b);
    if (fa == fb) return;
    if (father[fa] > father[fb]) {
        join(a, b, fa, fb);
    } else {
        join(b, a, fb, fa);
    }
}

void query(int a, int b) {
    if (find(a) == find(b)) {
        if (relation[a] == relation[b]) {
            printf("In the same gang.\n");
        } else {
            printf("In different gangs.\n");
        }
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
        memset(relation, 0, sizeof relation);
        scanf("%d %d", &n, &m);
        for (int i = 0; i < m; ++i) {
            char ch[2];
            int a, b;
            scanf("%s %d %d", ch, &a, &b);
            switch (ch[0]) {
                case 'D':
                    unite(a, b);
                    break;
                default:
                    query(a, b);
            }
        }
    }

    return 0;
}
