#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

int main() {

    ifstream cin("../a.in");
    ofstream cout("../a.out");

    int n, data, f[2][350] = {0}, now = 0, ans = 0;

    cin >> n;
    for (int i = 0; i < n; ++i) {
        now = 1 - now;
        for (int j = 0; j <= i; ++j) {
            cin >> data;
            if (i == 0) {
                f[now][j] = data;
            } else {
                if (j == 0) {
                    f[now][j] = f[1 - now][j] + data;
                } else if (j == i) {
                    f[now][j] = f[1 - now][j - 1] + data;
                } else {
                    f[now][j] = max(f[1 - now][j], f[1 - now][j - 1]) + data;
                }
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        ans = max(ans, f[now][i]);
    }

    cout << ans << endl;

    return 0;
}