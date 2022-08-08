#include <iostream>
#include <algorithm>

using namespace std;

#define MAX_N 500001

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

    int b[MAX_N], n;
    Node a[MAX_N];

    while (cin >> n && n != 0) {

        for (int i = 0; i < n; ++i) {
            scanf("%d", &a[i].value);
            a[i].index = i;
        }

        sort(a, a + n);

        cnt = 1;

        for (int i = 0; i < n; ++i) {

            if (i > 0 && a[i].value == a[i - 1].value) {
                b[a[i].index] = b[a[i - 1].index];
            } else {
                b[a[i].index] = cnt++;
            }
        }

        long long ans = 0;
        memset(sum, 0, sizeof sum);

        for (int i = 0; i < n; ++i) {
            ans += i - query(b[i]);
            add(b[i], 1);
        }

        printf("%lld\n", ans);
    }

    return 0;
}
