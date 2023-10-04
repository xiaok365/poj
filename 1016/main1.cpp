#include <iostream>
#include <cstring>

using namespace std;

#define MAX_N 81

void convert(int cur, char st_list[][MAX_N]) {
    int a[10] = {0};
    for (int i = 0; i < strlen(st_list[cur - 1]); ++i) {
        a[st_list[cur - 1][i] - '0']++;
    }

    int len = 0;
    for (int i = 0; i < 10; ++i) {
        if (a[i] == 0) continue;
        if (a[i] >= 10) {
            st_list[cur][len++] = a[i] / 10 + '0';
            st_list[cur][len++] = a[i] % 10 + '0';
        } else st_list[cur][len++] = a[i] + '0';
        st_list[cur][len++] = i + '0';
    }
    st_list[cur][len] = '\0';
}

int find(int cur, char st_list[][MAX_N]) {
    for (int i = cur - 1; i >= 0; --i) {
        if (strcmp(st_list[cur], st_list[i]) == 0) {
            return cur - i;
        }
    }
    return 0;
}

void solve(const char st[]) {
    char st_list[16][MAX_N];
    memset(st_list, 0, sizeof st_list);
    strcpy(st_list[0], st);
    for (int i = 1; i <= 15; ++i) {
        convert(i, st_list);
        if (strcmp(st_list[i], st_list[i - 1]) == 0) {
            if (i == 1) printf("%s is self-inventorying\n", st);
            else printf("%s is self-inventorying after %d steps\n", st, i - 1);
            return;
        }
        int len = find(i, st_list);
        if (len > 0) {
            printf("%s enters an inventory loop of length %d\n", st, len);
            return;
        }
    }
    printf("%s can not be classified after 15 iterations\n", st);
}

int main() {

    freopen("../a.in", "r", stdin);

    char st[MAX_N];

    while (~scanf("%s", st) && st[0] != '-') {
        solve(st);
    }

    return 0;
}
