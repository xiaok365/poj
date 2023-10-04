#include <iostream>

#define MAX_N 400001

char st[MAX_N];
int g_next[MAX_N], n;

void get_next() {
    int i = 0, j = -1;
    g_next[0] = -1;
    while (i < n) {
        if (j == -1 || st[i] == st[j]) {
            g_next[++i] = ++j;
        } else {
            j = g_next[j];
        }
    }
}

int main() {

    freopen("../a.in", "r", stdin);

    while (~scanf("%s", st)) {
        n = strlen(st);
        get_next();

        int ans[MAX_N], cnt = 0, i = n;
        while (g_next[i] >= 0) {
            ans[cnt++] = i;
            i = g_next[i];
        }

        for (i = cnt - 1; i >= 0; --i) {
            printf("%d ", ans[i]);
        }

        printf("\n");
    }

    return 0;
}
