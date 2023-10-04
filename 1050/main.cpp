#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

int calcMax(int *f, int n) {

    int temp = f[0], last = f[0];
    for (int i = 1; i < n; ++i) {

        if (last < 0) {
            temp = max(temp, f[i]);
            last = f[i];
        } else {
            temp = max(temp, last + f[i]);
            last = last + f[i];
        }
    }

    return temp;
}

int main() {

    ifstream cin("../a.in");
    ofstream cout("../a.out");

    int n, i, j, a[100][100], up[100][100], ans = 0x80000000;
    cin >> n;

    for (i = 0; i < n; ++i)
        for (j = 0; j < n; ++j) {
            cin >> a[i][j];
            if (i == 0) {
                up[i][j] = a[i][j];
            } else {
                up[i][j] = up[i - 1][j] + a[i][j];
            }
        }

    for (i = 0; i < n; ++i)
        for (j = i; j < n; ++j) {

            int f[100];
            for (int k = 0; k < n; ++k) {
                if (i == 0)
                    f[k] = up[j][k];
                else
                    f[k] = up[j][k] - up[i - 1][k];
            }
            ans = max(ans, calcMax(f, n));
        }

    cout << ans << endl;

    return 0;
}