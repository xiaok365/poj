#include <iostream>

using namespace std;

#define MAX_N 100001
int n, m, a[MAX_N];

int divide(int x) {
    int last = 0, ans = 1;
    for (int i = 0; i < n; ++i) {
        if (last + a[i] <= x) {
            last += a[i];
        } else {
            last = a[i];
            ans++;
        }
    }
    return ans;
}

int main() {

    freopen("../a.in", "r", stdin);

    while (~scanf("%d %d", &n, &m)) {
        int l = 0, r = 0;
        for (int i = 0; i < n; ++i) {
            scanf("%d", &a[i]);
            r += a[i];
            l = max(l, a[i]);
        }

        while (l < r) {
            int mid = (l + r) >> 1;
            if (divide(mid) > m) {
                l = mid + 1;
            } else {
                r = mid;
            }
        }

        printf("%d\n", l);
    }

    return 0;
}
