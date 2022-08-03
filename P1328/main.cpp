#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

#define  MAX_N 1000

struct Node {
    double x, y;
};

bool cmp(Node &a, Node &b) {
    return a.x < b.x;
}

int main() {

    freopen("../a.in", "r", stdin);

    int n, d, index = 0;

    Node pos[MAX_N], range[MAX_N];

    while (scanf("%d %d", &n, &d) && !(n == 0 && d == 0)) {

        for (int i = 0; i < n; ++i) {
            scanf("%lf %lf", &pos[i].x, &pos[i].y);
        }

        int ans = 1;
        for (int i = 0; i < n; ++i) {

            if (d < pos[i].y) {
                ans = -1;
                break;
            }

            range[i].x = pos[i].x - sqrt(pow((double) d, 2) - pow(pos[i].y, 2));
            range[i].y = pos[i].x + sqrt(pow((double) d, 2) - pow(pos[i].y, 2));
        }

        if (ans == -1) {
            printf("Case %d: %d\n", ++index, ans);
            continue;
        }

        sort(range, range + n, cmp);

        double last = range[0].y;
        for (int i = 1; i < n; ++i) {
            if (range[i].x > last) {
                last = range[i].y;
                ans++;
            } else {
                last = min(last, range[i].y);
            }
        }

        printf("Case %d: %d\n", ++index, ans);
    }

    return 0;
}