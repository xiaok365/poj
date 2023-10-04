#include <iostream>
#include <algorithm>

using namespace std;

#define MAX_N 20001
#define LL long long

struct Node {
    int v, x;

    bool operator<(const Node &other) const {
        return v < other.v;
    }
};

Node a[MAX_N];

int a_cnt[MAX_N];
LL a_sum[MAX_N];

int lowbit(int i) {
    return i & -i;
}

void add(int index, int c) {
    for (int i = index; i < MAX_N; i += lowbit(i)) {
        a_cnt[i] += 1;
        a_sum[i] += c;
    }
}

int query_cnt(int index) {
    int ret = 0;
    for (int i = index; i > 0; i -= lowbit(i)) {
        ret += a_cnt[i];
    }
    return ret;
}

LL query_sum(int index) {
    LL ret = 0;
    for (int i = index; i > 0; i -= lowbit(i)) {
        ret += a_sum[i];
    }
    return ret;
}


int main() {
    freopen("../a.in", "r", stdin);
    int n;

    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d %d", &a[i].v, &a[i].x);
    }

    sort(a, a + n);
    LL ans = 0, sum_x = 0;

    for (int i = 0; i < n; ++i) {
        int front = query_cnt(a[i].x), back = i - front;
        LL front_sum = query_sum(a[i].x), back_sum = sum_x - front_sum;
        ans += (a[i].x * front - front_sum + back_sum - a[i].x * back) * a[i].v;
        add(a[i].x, a[i].x);
        sum_x += a[i].x;
    }
    printf("%lld", ans);

    return 0;
}
