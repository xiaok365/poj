#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

int main() {

    ifstream cin("../a.in");
    ofstream cout("../a.out");

    int n, m, a[300], dis[300][300], f[300][31];
    cin >> n >> m;

    for (int i = 0; i < n; ++i) cin >> a[i];

    // init
    for (int i = 0; i < 300; ++i) {
        for (int j = 0; j < 31; ++j) {
            f[i][j] = 0x7fffffff;
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (j > i) {
                dis[i][j] = dis[i][j - 1] + a[j] - a[(i + j) >> 1];
            } else {
                dis[i][j] = 0;
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m && j <= i; ++j) {
            if (j == 0) {
                f[i][j] = dis[0][i];
            } else {
                for (int k = j - 1; k < i; ++k) {
                    f[i][j] = min(f[i][j], f[k][j - 1] + dis[k + 1][i]);
                }
            }
        }
    }

    cout << f[n - 1][m - 1] << endl;
    return 0;
}