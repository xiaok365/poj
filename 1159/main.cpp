#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

int main() {

    ifstream cin("../a.in");
    ofstream cout("../a.out");

    int i, j, n, f[3][5000] = {0};
    string st;
    cin >> n;
    cin >> st;

    for (int step = 1; step < n; ++step) {
        for (i = 0; i < n - step; ++i) {
            j = i + step;
            if (step == 1) {
                if (st[i] == st[j]) {
                    f[step % 3][i] = 0;
                } else {
                    f[step % 3][i] = 1;
                }
            } else {
                if (st[i] == st[j]) {
                    f[step % 3][i] = f[(step + 1) % 3][i + 1];
                } else {
                    f[step % 3][i] = min(f[(step - 1) % 3][i + 1], f[(step - 1) % 3][i]) + 1;
                }
            }
        }
    }

    cout << f[(n - 1) % 3][0] << endl;

    return 0;
}