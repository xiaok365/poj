#include <iostream>
#include <fstream>
#include<iomanip>

using namespace std;

const int MAXWIDTH = 1001;

struct Node {
    int width, price;
};

int main() {

    ifstream cin("../a.in");
    ofstream cout("../a.out");

    int t, n, i, j, k, tot[100], f[MAXWIDTH];
    Node device[100][100];
    cin >> t;
    while (t--) {
        cin >> n;
        for (i = 0; i < n; ++i) {
            cin >> tot[i];
            for (j = 0; j < tot[i]; ++j) {
                cin >> device[i][j].width >> device[i][j].price;
            }
        }

        for (i = 0; i < MAXWIDTH; ++i) f[i] = 0x7fffffff;
        for (i = 0; i < n; ++i) {
            for (j = 0; j < MAXWIDTH; ++j) {
                int minPrice = 0x7fffffff;
                for (k = 0; k < tot[i]; ++k) {
                    if (device[i][k].width >= j && device[i][k].price < minPrice) {
                        minPrice = device[i][k].price;
                    }
                }
                if (i == 0) {
                    f[j] = minPrice;
                } else {
                    if (f[j] == 0x7fffffff || minPrice == 0x7fffffff) {
                        f[j] = 0x7fffffff;
                    } else {
                        f[j] += minPrice;
                    }
                }
            }
        }
        double ans = 0;
        for (j = 0; j < MAXWIDTH; ++j) {
            if (f[j] != 0x7fffffff) {
                ans = max(ans, (double) j / f[j]);
            }
        }
        cout << setiosflags(ios::fixed) << setprecision(3) << ans << endl;
    }
    return 0;
}