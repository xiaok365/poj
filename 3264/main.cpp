#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

int high[50000][17], low[50000][17], n, q;

void solve() {
    // 枚举区间长度，2^j<=n
    for (int j = 1; (1 << j) <= n; ++j) {
        // 枚举左端点i，右端点i+2^j-1<=n-1
        for (int i = 0; i + (1 << j) <= n; ++i) {
            high[i][j] = max(high[i][j - 1], high[i + (1 << (j - 1))][j - 1]);
            low[i][j] = min(low[i][j - 1], low[i + (1 << (j - 1))][j - 1]);
        }
    }
}

int main() {
    ifstream cin("../a.in");
    ofstream cout("../a.out");
    cin >> n >> q;
    for (int i = 0; i < n; ++i) {
        cin >> high[i][0];
        low[i][0] = high[i][0];
    }
    solve();
    for (int i = 0; i < q; ++i) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        int j = (int) (log(b - a + 1.0) / log(2.0));
        int minHeight = min(low[a][j], low[b - (1 << j) + 1][j]);
        int maxHeight = max(high[a][j], high[b - (1 << j) + 1][j]);
        cout << maxHeight - minHeight << endl;
    }
    return 0;
}
