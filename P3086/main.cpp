#include <iostream>

using namespace std;

// 模拟计算
int solve(int m) {
    int ret = 0;
    for (int i = 1; i <= m; ++i) {
        ret += i * (i + 1) * (i + 2) / 2;
    }
    return ret;
}

int main() {

    freopen("../a.in", "r", stdin);

    int n, m;

    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> m;
//        printf("%d %d %d\n", i + 1, m, solve(m));
        // 数学公式
        int a = m * (m + 1);
        int b = (m + 2) * (m + 3);
        a >>= 1;
        b >>= 1;
        if (a & 1)b >>= 1; else a >>= 1;
        printf("%d %d %d\n", i + 1, m, a * b);
    }

    return 0;
}
