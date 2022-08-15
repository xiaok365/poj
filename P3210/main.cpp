#include <iostream>

int main() {
    freopen("../a.in", "r", stdin);

    int n;
    while (scanf("%d", &n) && n != 0) {
        if ((n & 1) == 0) printf("No Solution!\n");
        else printf("%d\n", n - 1);
    }
    return 0;
}
