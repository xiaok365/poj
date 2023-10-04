#include <iostream>
#include <cmath>

using namespace std;

int euler_phi(int n) {

    int m = sqrt(n + 0.5);
    int ans = n;
    for (int i = 2; i <= m; ++i) {
        if (n == 1) break;
        if (n % i == 0) {
            ans = ans / i * (i - 1);
            while (n % i == 0) n /= i;
        }
    }

    if (n > 1) ans = ans / n * (n - 1);
    return ans;
}

int main() {

    freopen("../a.in", "r", stdin);
    int n;
    while (scanf("%d", &n) && n != 0) {
        printf("%d\n", euler_phi(n));
    }
    return 0;
}
