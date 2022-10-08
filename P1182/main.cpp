#include <iostream>

using namespace std;

#define MAX_N 50001

int father[MAX_N], relation[MAX_N], n;

int find(int a) {
    if (a == father[a]) return a;

    int t = father[a];
    father[a] = find(father[a]);

    // 路径压缩，a与root的关系=a与父亲的关系+父亲与root的关系
    relation[a] = (relation[t] + relation[a]) % 3;
    return father[a];
}

void unite(int a, int b, int r) {
    int fa = find(a), fb = find(b);
    if (fa == fb) return;
    // fa的父亲指向fa
    father[fa] = fb;
    //a与fb的关系，a与b的关系+b与fb的关系
    int a2fb = r + relation[b];
    // fa与fb的关系，a与fb的关系-a与fa的关系
    relation[fa] = (a2fb - relation[a] + 3) % 3;
}

bool check(int a, int b, int r) {
    if (a > n || b > n || a < 1 || b < 1 || r == 1 && a == b) return false;
    if (find(a) == find(b)) {
        return (relation[a] - relation[b] + 3) % 3 == r;
    }
    return true;
}

void init() {
    for (int i = 0; i < MAX_N; ++i) {
        father[i] = i, relation[i] = 0;
    }
}

int main() {
    freopen("../a.in", "r", stdin);
    int k, r, a, b, lies = 0;
    init();
    scanf("%d %d", &n, &k);
    for (int i = 0; i < k; ++i) {
        scanf("%d %d %d", &r, &a, &b);
        r--;
        if (check(a, b, r)) {
            unite(a, b, r);
        } else {
            lies++;
        }
    }
    printf("%d", lies);
    return 0;
}