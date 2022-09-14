#include <iostream>
#include <vector>

#define LL long long

std::vector<LL> prime;

void get_prime(LL m) {
    for (LL i = 2; i * i <= m; ++i) {
        if (m == 1) break;
        if (m % i == 0) {
            prime.push_back(i);
        }
        while (m % i == 0) m /= i;
    }
    if (m != 1) prime.push_back(m);
}

LL pow(LL a, LL b) {
    LL ans = 1;
    while (b) {
        if (b & 1) ans *= a;
        a *= a;
        b >>= 1;
    }
    return ans;
}

int main() {

    freopen("../a.in", "r", stdin);

    LL m, n;
    while (~scanf("%lld %lld", &n, &m)) {
        prime.clear();
        get_prime(m);
        LL ans = pow(m, n);
        for (int i = 1; i < (1 << prime.size()); ++i) {
            LL k = 1;
            int cnt = 0;
            for (int j = 0; j < prime.size(); ++j) {
                if (i & (1 << j)) {
                    k *= prime[j];
                    cnt++;
                }
            }
            LL p = pow(m / k, n);
            if (cnt & 1) ans -= p; else ans += p;
        }
        printf("%lld\n", ans);
    }

    return 0;
}
