#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

struct Node {
    int l, w;
};

bool cmp(const Node &a, const Node &b) {
    if (a.l == b.l) {
        return a.w < b.w;
    } else {
        return a.l < b.l;
    }
}

int main() {

    ifstream cin("../a.in");
    ofstream cout("../a.out");

    int t, n, i, j, f[5000];
    Node a[5000];
    cin >> t;
    while (t--) {
        cin >> n;
        for (i = 0; i < n; ++i) {
            cin >> a[i].l >> a[i].w;
        }
        sort(a, a + n, cmp);
        int ans = 0;
        for (i = 0; i < n; ++i) {
            f[i] = 1;
            for (j = 0; j < i; ++j) {
                if (a[j].w > a[i].w) {
                    f[i] = max(f[i], f[j] + 1);
                }
            }
            ans = max(ans, f[i]);
        }
        cout << ans << endl;
    }
    return 0;
}