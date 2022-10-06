#include <iostream>
#include <cstring>

int main() {
    freopen("../a.in", "r", stdin);
    int n;
    while (scanf("%d", &n) && n > 0) {
        int min = 0x7fffffff, max = 0, a, b, c;
        char min_name[20], max_name[20], name[20];
        for (int i = 0; i < n; ++i) {
            scanf("%d %d %d %s", &a, &b, &c, name);
            int t = a * b * c;
            if (t > max) {
                max = t;
                strcpy(max_name, name);
            }
            if (t < min) {
                min = t;
                strcpy(min_name, name);
            }
        }
        printf("%s took clay from %s.\n", max_name, min_name);
    }

    return 0;
}