#include <iostream>

using namespace std;

int lowbit(int x) {
    return x & -x;
}

int main() {

    freopen("../a.in", "r", stdin);
    freopen("../a.out", "w", stdout);
    int n, x;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> x;
        printf("%d %d\n", x - lowbit(x) + 1, x + lowbit(x) - 1);
    }

    return 0;
}
