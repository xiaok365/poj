#include <iostream>
#include "sort.h"

using namespace std;

#define MAX_NUM 100001

struct Point {
    int index, x, y;

    bool operator<=(const Point &node) const {
        if (x == node.x) {
            return y >= node.y;
        }
        return x < node.x;
    }
};

int lowbit(int x) {
    return x & -x;
}

void add(int sum[], int index, int x) {
    while (index <= MAX_NUM) {
        sum[index] += x;
        index += lowbit(index);
    }
}

int query(const int sum[], int index) {
    int ret = 0;
    while (index > 0) {
        ret += sum[index];
        index -= lowbit(index);
    }
    return ret;
}

int main() {
    freopen("../a.in", "r", stdin);
    freopen("../a.out", "w", stdout);
    int n;
    scanf("%d", &n);
    while (n > 0) {
        Point cow[MAX_NUM];
        for (int i = 0; i < n; ++i) {
            scanf("%d%d", &cow[i].x, &cow[i].y);
            cow[i].y++;
            cow[i].index = i;
        }
        sort(cow, 0, n - 1);
        int sum[MAX_NUM] = {0}, ans[MAX_NUM] = {0};
        for (int i = 0; i < n; ++i) {
            if (i > 0 && cow[i].x == cow[i - 1].x && cow[i].y == cow[i - 1].y) {
                ans[cow[i].index] = ans[cow[i - 1].index];
            } else {
                ans[cow[i].index] = i - query(sum, cow[i].y - 1);
            }
            add(sum, cow[i].y, 1);
        }
        for (int i = 0; i < n - 1; ++i) {
            printf("%d ", ans[i]);
        }
        printf("%d\n", ans[n - 1]);
        scanf("%d", &n);
    }
    return 0;
}
