#include <iostream>
#include <fstream>

using namespace std;

const int MAXM = 200, MAXN = 200;

bool map[MAXN][MAXM] = {false}, visit[MAXM];
int n, m, x[MAXM], y[MAXN];

bool hungary(int u) {
    for (int i = 0; i < m; ++i) {
        if (!visit[i] && map[u][i]) {
            visit[i] = true;
            if (y[i] == -1 || hungary(y[i])) {
                x[u] = i;
                y[i] = u;
                return true;
            }
        }
    }
    return false;
}

void init() {
    memset(x, 0xff, MAXM * 4);
    memset(y, 0xff, MAXN * 4);
    memset(map, false, MAXN * MAXM);
}

int main() {

    ifstream cin("../a.in");
    ofstream cout("../a.out");

    int i, j, num, stall;

    while (cin >> n >> m) {
        init();
        for (i = 0; i < n; ++i) {
            cin >> num;
            for (j = 0; j < num; ++j) {
                cin >> stall;
                map[i][stall - 1] = true;
            }
        }
        int ans = 0;
        for (i = 0; i < n; ++i) {
            if (x[i] == -1) {
                memset(visit, false, MAXM);
                if (hungary(i)) {
                    ans++;
                }
            }
        }
        cout << ans << endl;
    }
    return 0;
}