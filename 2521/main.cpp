#include <iostream>

using namespace std;

int main() {
    freopen("../a.in", "r", stdin);
    int n, m, p, c;
    while (cin >> n >> m >> p >> c && !(n == 0 && m == 0 && p == 0 && c == 0)) {
        int give = m + c - p;
        int cost = n + c;
        printf("%d\n", cost - give);
    }

    return 0;
}
