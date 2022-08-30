#include <iostream>
#include <algorithm>

using namespace std;

#define MAX_N 1001

struct Node {
    int x, y;

    bool operator<(const Node &node) const {
        if (x == node.x) return y <= node.y;
        return x < node.x;
    }
};

int sum[MAX_N], n, east, west;

int lowbit(int x) {
    return x & -x;
}

void add(int i, int x) {

    while (i <= west) {
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

    int scenario;
    Node a[MAX_N * MAX_N];

    scanf("%d", &scenario);
    for (int t = 0; t < scenario; ++t) {
        scanf("%d %d %d", &east, &west, &n);
        for (int i = 0; i < n; ++i) scanf("%d %d", &a[i].x, &a[i].y);

        sort(a, a + n);

        long long ans = 0;
        memset(sum, 0, sizeof sum);

        for (int i = 0; i < n; ++i) {
            ans += i - query(a[i].y);
            add(a[i].y, 1);
        }

        printf("Test case %d: %lld\n", t + 1, ans);
    }

    return 0;
}
