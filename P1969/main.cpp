#include <iostream>

#define MAX_N 4473

int num[MAX_N];

int main() {
    freopen("../a.in", "r", stdin);

    int cnt = 0;
    for (int i = 0; i < MAX_N; ++i) {
        num[cnt++] = (i + 1) * i / 2;
    }

    int n;
    while (~scanf("%d", &n)) {
        int l = 0, r = cnt - 1;
        while (l < r) {
            int mid = (l + r) >> 1;
            if (num[mid] < n) {
                l = mid + 1;
            } else {
                r = mid;
            }
        }
        int offset = 1;
        if (l >= 1) offset = n - num[l - 1];

        if (l & 1) {
            printf("TERM %d IS %d/%d\n", n, l + 1 - offset, offset);
        } else {
            printf("TERM %d IS %d/%d\n", n, offset, l + 1 - offset);
        }
    }

    return 0;
}
