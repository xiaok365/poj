#include <iostream>
#include <cstring>

using namespace std;

#define MAXN 1000001

char st[MAXN];
int g_next[MAXN], n;

int max(int a, int b) {
    return a > b ? a : b;
}

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

    int ans = 1, k = i - g_next[i];

    if (i % k == 0) {
        ans = max(ans, i / k);
    }
    printf("%d\n", ans);
}

int main() {

    freopen("../a.in", "r", stdin);

    while (scanf("%s", st) && st[0] != '.') {
        n = (int) strlen(st);
        get_next();
    }

    return 0;
}
