#include <iostream>
#include <fstream>

using namespace std;

int main() {

    ifstream cin("../a.in");
    ofstream cout("../a.out");

    int t, n, a[200], from, to;
    cin >> t;
    while (t--) {
        memset(a, 0, 200 * 4);
        cin >> n;
        for (int i = 0; i < n; ++i) {
            cin >> from >> to;
            if (from > to) {
                from ^= to ^= from ^= to;
            }
            for (int j = (from - 1) >> 1; j <= (to - 1) >> 1; ++j) {
                a[j]++;
            }
        }
        int ans = 0;
        for (int i = 0; i < 200; ++i) {
            ans = max(ans, a[i]);
        }
        cout << ans * 10 << endl;
    }
    return 0;
}