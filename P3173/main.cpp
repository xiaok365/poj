#include <iostream>

using namespace std;

int main() {

    freopen("../a.in", "r", stdin);

    int n, s;
    cin >> n >> s;

    int a[21][21];

    memset(a, 0xff, sizeof a);

    for (int j = 0; j < n; ++j) {
        for (int i = 0; i <= j; ++i) {
            a[i][j] = s;
            s++;
            if (s > 9) s = 1;
        }
    }


    for (int i = 0; i < n; ++i) {

        for (int j = 0; j < n; ++j) {
            if (a[i][j] == -1) printf("  "); else printf("%d ", a[i][j]);
        }
        printf("\n");
    }

    return 0;
}
