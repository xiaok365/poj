#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

struct Node {
    int value;
    int num;
};

int countOne(int x) {
    int total = 0;
    while (x > 0) {
        total++;
        x &= x - 1;
    }
    return total;
}

void init(Node state[], int &stateCnt, int m) {

    for (int i = 0; i < 1 << m; ++i) {
        if (!(i & i << 1) && !(i & i << 2)) {
            state[stateCnt].value = i;
            state[stateCnt].num = countOne(i);
            stateCnt++;
        }
    }
}

bool isConflict(Node state[], int i, int j) {

    return (state[i].value & state[j].value) > 0;
}

int main() {

    ifstream cin("../a.in");
    ofstream cout("../a.out");

    int n, m, stateCnt = 0, line[100], f[2][60][60] = {0};
    Node state[100];
    char ch;
    cin >> n >> m;

    init(state, stateCnt, m);

    for (int i = 0; i < n; ++i) {
        int t = 0;
        for (int j = 0; j < m; ++j) {
            cin >> ch;
            t <<= 1;
            if (ch == 'H') {
                t += 1;
            }
        }
        line[i] = t;
    }

    int i, current, last, preLast, now = 0;

    // 初始化第一行
    for (i = 0; i < stateCnt; ++i) {
        if ((line[0] & state[i].value) == 0) {
            f[0][i][0] = state[i].num;
        }
    }
    for (i = 1; i < n; ++i) {
        now = 1 - now;
        for (current = 0; current < stateCnt; ++current) {
            for (last = 0; last < stateCnt; ++last) {
                if (!isConflict(state, current, last) && (line[i] & state[current].value) == 0) {
                    for (preLast = 0; preLast < stateCnt; ++preLast) {
                        if (!isConflict(state, current, preLast)) {
                            f[now][current][last] = max(f[now][current][last],
                                                        f[1 - now][last][preLast] + state[current].num);
                        }
                    }
                }
            }
        }
    }

    int ans = 0;
    for (current = 0; current < stateCnt; ++current)
        for (last = 0; last < stateCnt; ++last) {
            ans = max(ans, f[now][current][last]);
        }
    cout << ans << endl;

    return 0;
}