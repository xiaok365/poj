#include <iostream>
#include <string>

using namespace std;

#define MAXM 10001

int g_next[MAXM];

void get_next(string &sub) {
    int i = 0, j = -1, m = sub.size();
    g_next[0] = -1;
    while (i < m) {
        if (j == -1 || sub[i] == sub[j]) {
            g_next[++i] = ++j;
        } else {
            j = g_next[j];
        }
    }
}

int kmp(string &src, string &sub) {

    int t = 0, i = 0, j = 0, n, m;
    n = src.size();
    m = sub.size();
    get_next(sub);
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
    string src, sub;

    cin >> t;
    for (int i = 0; i < t; ++i) {
        cin >> sub >> src;
        printf("%d\n", kmp(src, sub));
    }

    return 0;
}