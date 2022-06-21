#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

int main() {

    ifstream cin("../a.in");
    ofstream cout("../a.out");

    int n, m, a[100][100], f[100][100] = {0};

    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> a[i][j];
        }
    }

    for (int i = 0; i < 100; ++i) {
        for (int j = 0; j < 100; ++j) {
            f[i][j] = 0x80000000;
        }
    }

    f[0][0] = a[0][0];
    for (int i = 1; i < m; ++i) {
        f[0][i] = max(f[0][i - 1], a[0][i]);
    }

    for (int i = 1; i < n; ++i) {
        for (int j = i; j < m; ++j) {

            f[i][j] = max(f[i][j - 1], f[i - 1][j - 1] + a[i][j]);
        }
    }

    cout << f[n - 1][m - 1] << endl;
    return 0;
}