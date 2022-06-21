#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

struct Goods {
    int price;
    int level;
    int replace;
    int itemSn[100];
    int discount[100];
};

int f[100], m;
bool visit[100];
Goods a[100];

int solve(int goodSn, int minLevel, int maxLevel) {

    f[goodSn] = a[goodSn].price;
    for (int i = 0; i < a[goodSn].replace; ++i) {
        int curLevel = a[a[goodSn].itemSn[i]].level;

        if (!visit[a[goodSn].itemSn[i]] && abs(curLevel - minLevel) <= m && abs(curLevel - maxLevel) <= m) {
            visit[a[goodSn].itemSn[i]] = true;
            f[goodSn] = min(f[goodSn], solve(a[goodSn].itemSn[i], min(minLevel, curLevel), max(maxLevel, curLevel))
                                       + a[goodSn].discount[i]);
            visit[a[goodSn].itemSn[i]] = false;
        }
    }

    return f[goodSn];
}

int main() {

    ifstream cin("../a.in");
    ofstream cout("../a.out");

    int n;
    cin >> m >> n;

    for (int i = 0; i < n; ++i) {
        cin >> a[i].price >> a[i].level >> a[i].replace;
        for (int j = 0; j < a[i].replace; ++j) {
            cin >> a[i].itemSn[j] >> a[i].discount[j];
            a[i].itemSn[j]--;
        }
    }

    for (int i = 0; i < 100; ++i) {
        f[i] = 0x7fffffff;
        visit[i] = false;
    }

    cout << solve(0, a[0].level, a[0].level) << endl;

    return 0;
}