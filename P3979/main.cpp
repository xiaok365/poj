#include <iostream>

int gcd(int a, int b) {
    if (b == 0) return a;
    else return gcd(b, a % b);
}

int main() {
    freopen("../a.in", "r", stdin);

    char st[8];

    while (~scanf("%s", st)) {
        int x1 = st[0] - '0', y1 = st[2] - '0', x2 = st[4] - '0', y2 = st[6] - '0';

        int num;
        if (st[3] == '+') {
            num = x1 * y2 + x2 * y1;
        } else {
            num = x1 * y2 - x2 * y1;
        }
        int den = y1 * y2;

        int g = gcd(den, num);
        if (num % den == 0) printf("%d\n", num / den);
        else {
            if (g < 0) g = -g;
            printf("%d/%d\n", num / g, den / g);
        }
    }

    return 0;
}
