#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

struct Node {
    int p, d;
};
const int MAXN = 10001;

int n, father[MAXN];
Node a[MAXN];

bool cmp(Node &a, Node &b) {
    return a.p > b.p;
}

int findFather(int x) {
    if (father[x] == -1) return x;
    int root = findFather(father[x]);
    father[x] = root;
    return root;
}

int main() {

    ifstream cin("../a.in");
    ofstream cout("../a.out");

    while (cin >> n) {
        for (int i = 0; i < n; ++i) {
            cin >> a[i].p >> a[i].d;
        }
        sort(a, a + n, cmp);
        memset(father, 0xff, MAXN * 4);
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            int space = findFather(a[i].d);
            if (space > 0) {
                ans += a[i].p;
                father[space] = space - 1;
            }
        }
        cout << ans << endl;
    }
    return 0;
}