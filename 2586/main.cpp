#include <iostream>

using namespace std;

int main() {

    freopen("../a.in", "r", stdin);

    int s, d;
    while (~scanf("%d %d", &s, &d)) {
        int j = 0;
        for (; j < 5; ++j) {
            if (s * j > d * (5 - j)) {
                break;
            }
        }
        --j;

        int t;
        if (j <= 2) {
            t = s * (j * 2 + j) - d * ((5 - j) * 2 + 2 - j);
        } else {
            t = s * (j * 2 + 2) - d * (5 - j) * 2;
        }
        if (t > 0) {
            printf("%d\n", t);
        } else {
            printf("Deficit\n");
        }
    }
    return 0;
}
