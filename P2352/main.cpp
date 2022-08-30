#include <iostream>
#include <algorithm>

using namespace std;

#define MAX_N 15001
#define MAX_M 32002

int sum[MAX_M], cnt = 0;

struct Point {
    int x, y;

    bool operator<(const Point &node) const {
        if (x == node.x) {
            return y <= node.y;
        }
        return x < node.x;
    }

    bool operator==(const Point &node) const {
        return x == node.x && y == node.y;
    }
};

int lowbit(int x) {
    return x & -x;
}

void add(int i, int x) {
    while (i <= cnt) {
        sum[i] += x;
        i += lowbit(i);
    }
}

int query(int i) {
    int ret = 0;
    while (i > 0) {
        ret += sum[i];
        i -= lowbit(i);
    }
    return ret;
}

int main() {
    freopen("../a.in", "r", stdin);

    int n;
    Point a[MAX_N];

    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        scanf("%d%d", &a[i].x, &a[i].y);
        a[i].y++;
        cnt = max(cnt, a[i].y);
    }

    sort(a, a + n);

    int ans[MAX_N] = {0};
    memset(sum, 0, sizeof sum);

    for (int i = 0; i < n; ++i) {
        ans[query(a[i].y)]++;
        add(a[i].y, 1);
    }

    for (int i = 0; i < n; ++i) printf("%d\n", ans[i]);

    return 0;
}
