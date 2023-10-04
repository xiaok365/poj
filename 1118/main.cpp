#include <iostream>
#include <algorithm>

using namespace std;

#define MAX_N 710

struct Node {
    int x, y;

    bool operator<(const Node &other) const {
        if (x == other.x) return y < other.y;
        return x < other.x;
    }
};

inline int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int main() {

    freopen("../a.in", "r", stdin);

    int n;
    Node a[MAX_N], ratio[MAX_N];

    while (~scanf("%d", &n) && n > 0) {
        for (int i = 0; i < n; ++i) scanf("%d %d", &a[i].x, &a[i].y);
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            int cnt = 0;
            for (int j = 0; j < n; ++j) {
                if (i == j) continue;
                int x = a[j].x - a[i].x;
                int y = a[j].y - a[i].y;
                int g = gcd(x, y);
                if (x == 0) {
                    ratio[cnt].x = 0, ratio[cnt++].y = 1;
                } else if (y == 0) {
                    ratio[cnt].x = 0, ratio[cnt++].y = 0;
                } else {
                    ratio[cnt].x = x / g, ratio[cnt++].y = y / g;
                }
            }
            sort(ratio, ratio + cnt);
            int len = 1;
            for (int j = 1; j <= cnt; ++j) {
                if (ratio[j].x == ratio[j - 1].x && ratio[j].y == ratio[j - 1].y) {
                    len++;
                } else {
                    if (len > ans) ans = len;
                    len = 1;
                }
            }
        }
        printf("%d\n", ans + 1);
    }
    return 0;
}
