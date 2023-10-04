#include <iostream>
#include <cstdio>
#include <fstream>

using namespace std;

const int MAXP = 100;
const int MAXN = 300;
bool map[MAXP][MAXN];
// x表示课程匹配的学生，y表示学生匹配的课程
int x[MAXP], y[MAXN];

void init() {
    memset(map, false, MAXP * MAXN);
    memset(x, -1, MAXP * 4);
    memset(y, -1, MAXN * 4);
}

bool hungary(int s, int n, bool visit[]) {

    for (int i = 0; i < n; ++i) {
        if (map[s][i] && !visit[i]) {
            visit[i] = true;
            if (y[i] == -1 || hungary(y[i], n, visit)) {
                x[s] = i;
                y[i] = s;
                return true;
            }
        }
    }
    return false;
}

int main() {

    ifstream cin("../a.in");
    ofstream cout("../a.out");

    int t, p, n, m, data;
//    cin >> t;
    scanf("%d", &t);
    while (t--) {
        init();
//        cin >> p >> n;
        scanf("%d%d", &p, &n);
        for (int i = 0; i < p; ++i) {
//            cin >> m;
            scanf("%d", &m);
            while (m--) {
//                cin >> data;
                scanf("%d", &data);
                map[i][data - 1] = true;
            }
        }

        int ans = 0;
        bool visit[MAXN];
        for (int i = 0; i < p; ++i) {
            if (x[i] == -1) {
                memset(visit, false, MAXN);
                if (hungary(i, n, visit)) {
                    ans++;
                }
            }
        }
        if (p == ans) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }

    return 0;
}