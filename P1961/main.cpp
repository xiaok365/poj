#include <iostream>

using namespace std;

#define MAXN 1000001
char st[MAXN];
int g_next[MAXN], n;

void get_next() {
    int i = 0, j = -1;
    g_next[0] = -1;
    while (i < n) {
        if (j == -1 || st[i] == st[j]) {
            g_next[++i] = ++j;
            int k = i - g_next[i];
            if (i % k == 0 && i / k > 1) {
                printf("%d %d\n", i, i / k);
            }
        } else {
            j = g_next[j];
        }
    }
}

int main() {

    freopen("../a.in", "r", stdin);

    int i = 1;
    while (scanf("%d", &n) && n != 0) {
        scanf("%s", st);
        printf("Test case #%d\n", i++);
        get_next();
        printf("\n");
    }


    return 0;
}
