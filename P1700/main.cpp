#include <iostream>
#include <algorithm>

using namespace std;

#define MAX_N 1001

int n, a[MAX_N];

int solve() {
    sort(a, a + n);
    int ans = 0, left = n;
    while (left) {
        switch (left) {
            case 1:
                ans += a[0], left = 0;
                break;
            case 2:
                ans += a[1], left = 0;
                break;
            case 3:
                ans += a[0] + a[1] + a[2], left = 0;
                break;
            default:
                ans += min(a[left - 1] + a[left - 2] + 2 * a[0], a[0] + 2 * a[1] + a[left - 1]);
                left -= 2;
        }
    }
    return ans;
}

int main() {
    freopen("../a.in", "r", stdin);
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
        printf("%d\n", solve());
    }
    return 0;
}
