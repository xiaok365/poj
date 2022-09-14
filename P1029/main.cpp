#include <iostream>

#define MAX_N 1001

int main() {

    freopen("../a.in", "r", stdin);

    int n, m;

    while (~scanf("%d %d", &n, &m)) {

        int less[MAX_N] = {0}, more[MAX_N] = {0}, not_equal = 0;
        bool flag[MAX_N] = {false};

        for (int i = 0; i < m; ++i) {

            int p, a[MAX_N] = {0};
            scanf("%d", &p);
            for (int j = 0; j < 2 * p; ++j) scanf("%d", &a[j]);

            char ch;
            getchar(), ch = getchar();
            switch (ch) {
                case '<':
                    for (int j = 0; j < p; ++j) {
                        less[a[j]]++, more[a[j + p]]++;
                    }
                    not_equal++;
                    break;
                case '>':
                    for (int j = 0; j < p; ++j) {
                        more[a[j]]++, less[a[j + p]]++;
                    }
                    not_equal++;
                    break;
                default:
                    for (int j = 0; j < 2 * p; ++j) flag[a[j]] = true;
            }
        }

        for (int i = 1; i <= n; ++i) {
            if (less[i] + more[i] < not_equal || less[i] && more[i]) {
                flag[i] = true;
            }
        }

        int cnt = 0, k = 0;
        for (int j = 1; j <= n; ++j) {
            if (!flag[j]) {
                cnt++, k = j;
            }
        }
        printf("%d\n", cnt == 1 ? k : 0);
    }

    return 0;
}
