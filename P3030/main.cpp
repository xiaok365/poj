#include <iostream>

int main() {

    freopen("../a.in", "r", stdin);
    int n, r, e, c;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d %d %d", &r, &e, &c);
        if (r == e - c) printf("does not matter\n");
        else if (r < e - c) printf("advertise\n");
        else printf("do not advertise\n");
    }
    return 0;
}
