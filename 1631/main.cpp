#include <iostream>

#define MAX_N 40001

using namespace std;

int n, pre[MAX_N];

int lowbit(int x) {
    return x & -x;
}

void update(int index, int x) {
    while (index <= n) {
        pre[index] = max(pre[index], x);
        index += lowbit(index);
    }
}

int query(int index) {
    int ret = 0;
    while (index > 0) {
        ret = max(ret, pre[index]);
        index -= lowbit(index);
    }
    return ret;
}

int main() {
    freopen("../a.in", "r", stdin);

    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        memset(pre, 0, sizeof pre);
        int d;
        for (int i = 0; i < n; ++i) {
            scanf("%d", &d);
            int k = query(d);
            update(d, k + 1);
        }
        printf("%d\n", query(n));
    }
    return 0;
}
