#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

using namespace std;

int main() {

    ifstream cin("../a.in");
    ofstream cout("../a.out");

    string a, b;
    int f[1001][1001] = {0};

    while (cin >> a >> b) {

        memset(f, 0, 1001 * 1001 * 4);

        for (int i = 1; i <= a.size(); ++i)
            for (int j = 1; j <= b.size(); ++j) {

                f[i][j] = max(f[i][j - 1], f[i - 1][j]);
                if (a[i - 1] == b[j - 1]) {
                    f[i][j] = max(f[i][j], f[i - 1][j - 1] + 1);
                }
            }

        cout << f[a.size()][b.size()] << endl;
    }

    return 0;
}