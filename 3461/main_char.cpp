#include <iostream>
#include <cstring>

using namespace std;

#define MAXN 1000001
#define MAXM 10001

int g_next[MAXM], n, m;
char src[MAXN], sub[MAXM];

void get_next() {
    int i = 0, j = -1;
    g_next[0] = -1;
    while (i < m) {
        if (j == -1 || sub[i] == sub[j]) {
            g_next[++i] = ++j;
        } else {
            j = g_next[j];
        }
    }
}

int kmp() {
    int t = 0, i = 0, j = 0;
    get_next();
    while (i < n && j < m) {
        if (j == -1 || src[i] == sub[j]) {
            i++;
            j++;
        } else {
            j = g_next[j];
        }
        if (j == m) {
            t++;
            j = g_next[j];
        }
    }
    return t;
}

int main() {
    freopen("../a.in", "r", stdin);

    int t;
    cin >> t;
    for (int i = 0; i < t; ++i) {
        scanf("%s %s", sub, src);
        n = (int) strlen(src);
        m = (int) strlen(sub);
        printf("%d\n", kmp());
    }

    return 0;
}