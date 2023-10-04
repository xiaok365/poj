#include <iostream>

int main() {

    freopen("../a.in", "r", stdin);

    int t, a, b;
    scanf("%d", &t);
    while (t--) {
        scanf("%d:%d", &a, &b);
        if (b != 0) {
            printf("0\n");
        } else {
            printf("%d\n", (a + 11) % 24 + 1);
        }
    }
    return 0;
}
