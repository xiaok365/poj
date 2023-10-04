#include <iostream>

using namespace std;

int main() {
    freopen("../a.in", "r", stdin);
    int t, n, m, d;
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d", &n, &m);
        int min_t = 0, max_t = 0;
        for (int i = 0; i < m; ++i) {
            scanf("%d", &d);
            min_t = max(min_t, min(d, n - d));
            max_t = max(max_t, max(d, n - d));
        }
        printf("%d %d\n", min_t, max_t);
    }
    return 0;
}
