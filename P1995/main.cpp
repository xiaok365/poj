#include <iostream>

int mul(int a, int b, int c) {
    int ret = 0;
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
int pow(int a, int b, int p) {
    int ret = 1;
    while (b) {
        if (b & 1) ret = mul(ret, a, p);
        a = mul(a, a, p);
        b >>= 1;
    }
    return ret;
}

int main() {

    freopen("../a.in", "r", stdin);

    int t, m, h, a, b;
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d", &m, &h);
        int ret = 0;
        for (int i = 0; i < h; ++i) {
            scanf("%d %d", &a, &b);
            ret = (ret + pow(a, b, m)) % m;
        }
        printf("%d\n", ret);
    }
    return 0;
}
