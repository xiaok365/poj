#include <iostream>
#include <cstdio>
#include <ctime>

typedef long long LL;

LL mul(LL a, LL b, LL c) {
    LL ret = 0;
    while (b) {
        if (b & 1) {
            ret += a;
            if (ret >= c) ret %= c;
        }
        b >>= 1;
        a <<= 1;
        if (a >= c) a %= c;
    }
    return ret;
}

// a^b%p
LL pow(LL a, LL b, LL p) {
    LL ret = 1;
    while (b) {
        if (b & 1) ret = mul(ret, a, p);
        a = mul(a, a, p);
        b >>= 1;
    }
    return ret;
}

bool witness(LL d, LL n) {

    LL a = rand() % (n - 2) + 2;
    LL x = pow(a, d, n);
    if (x == 1 || x == n - 1) return true;

    while (d <= n - 1) {
        x = mul(x, x, n);
        d <<= 1;
        if (x == 1) return false;
        if (x == n - 1) return true;
    }

    return false;
}

bool miller_rabin(LL n) {

    if (n == 2) return true;
    if (n < 2 || 0 == (n & 1)) return false;

    LL d = n - 1;
    while ((d & 1) == 0) d >>= 1;

    for (int i = 0; i < 20; ++i) {
        if (!witness(d, n)) {
            return false;
        }
    }
    return true;
}


LL gcd(LL a, LL b) {
    if (a == 0) return 1;
    if (a < 0) return gcd(-a, b);
    while (b) {
        LL t = a % b;
        a = b;
        b = t;
    }
    return a;
}

LL pollard_rho(LL n) {
    if (n == 1) return n;
    if (n % 2 == 0) return 2;
    LL x = rand() % (n - 2) + 2;
    LL c = rand() % (n - 1) + 1;
    LL y = x, d = 1, i = 1, k = 2;
    while (d == 1) {
        i++;
        x = (mul(x, x, n) + c) % n;
        d = gcd(x - y, n);
        if (d > 1 && d < n) return d;
        if (y == x) return n;
        if (i == k) y = x, k <<= 1;
    }

    return d;
}

LL factor[100];
int tol;

void find_fac(LL n) {
    if (miller_rabin(n)) {
        factor[tol++] = n;
        return;
    }
    LL p = n;
    while (p >= n) p = pollard_rho(p);
    find_fac(p);
    find_fac(n / p);
}

int main() {

    freopen("../a.in", "r", stdin);

    int t;
    LL n;

    srand(time(NULL));
    scanf("%d", &t);
    while (t--) {
        scanf("%lld", &n);
        if (miller_rabin(n)) {
            printf("Prime\n");
            continue;
        }
        tol = 0;
        find_fac(n);
        LL ans = factor[0];
        for (int i = 1; i < tol; i++)
            if (factor[i] < ans) ans = factor[i];
        printf("%lld\n", ans);
    }
    return 0;
}
