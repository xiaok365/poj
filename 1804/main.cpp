#include <iostream>
#include <algorithm>

using namespace std;

#define MAX_N 1001

struct Node {
    int index, value;

    bool operator<(const Node &rhs) const {
        return value < rhs.value;
    }
};

int sum[MAX_N], cnt;

int lowbit(int x) {
    return x & -x;
}

void add(int i, int x) {

    while (i < cnt) {
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

    int b[MAX_N], n, scenario;
    Node a[MAX_N];

    scanf("%d", &scenario);
    for (int t = 0; t < scenario; ++t) {
        scanf("%d", &n);

        for (int i = 0; i < n; ++i) {
            scanf("%d", &a[i].value);
            a[i].index = i;
        }

        // 离散
        sort(a, a + n);
        cnt = 1;
        for (int j = 0; j < n; ++j) {
            if (j > 0 && a[j].value == a[j - 1].value) {
                b[a[j].index] = b[a[j - 1].index];
            } else {
                b[a[j].index] = cnt++;
            }
        }

        long long ans = 0;
        memset(sum, 0, sizeof sum);

        for (int i = 0; i < n; ++i) {
            ans += i - query(b[i]);
            add(b[i], 1);
        }

        printf("Scenario #%d:\n", t + 1);
        printf("%lld\n\n", ans);
    }

    return 0;
}
