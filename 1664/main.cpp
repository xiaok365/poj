#include <iostream>
#include <fstream>

using namespace std;

int f[11][11];

int solve(int m, int n) {
    if (m < 0) return 0;
    if (m == 0 || n == 1) return 1;
    return solve(m - n, n) + solve(m, n - 1);
}

int solve1(int m, int n) {

    if (f[m][n] != -1) return f[m][n];
    if (m < n) {
        f[m][n] = 0;
        return f[m][n];
    }
    if (m == n || n == 1) {
        f[m][n] = 1;
        return f[m][n];
    }

    f[m][n] = 0;
    for (int i = 1; i <= n; ++i) {
        f[m][n] += solve1(m - n, i);
    }

    return f[m][n];
}

int main() {

    ifstream cin("../a.in");
    ofstream cout("../a.out");

    int t, n, m;

    memset(f, 0xff, sizeof(f));

    cin >> t;
    while (t--) {
        cin >> m >> n;
//        cout << solve(m, n) << endl;
        int ans = 0;
        for (int i = 1; i <= n; ++i) {
            ans += solve1(m, i);
        }
        cout << ans << endl;
    }

    return 0;
}