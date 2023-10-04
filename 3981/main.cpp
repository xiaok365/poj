#include <iostream>

using namespace std;
#define MAX_N 1001

int main() {

    freopen("../a.in", "r", stdin);
    char st[MAX_N];

    while (~scanf("%[^\n]", st) && getchar()) {
        int len = strlen(st);

        int i = 0, cnt = 0;
        char ans[MAX_N] = {0};

        while (i <= len - 3) {
            if (st[i] == 'y' && st[i + 1] == 'o' && st[i + 2] == 'u') {
                i += 3;
                ans[cnt++] = 'w', ans[cnt++] = 'e';
            } else {
                ans[cnt++] = st[i++];
            }
        }
        if (i < len) {
            ans[cnt++] = st[i++], ans[cnt] = st[i];
        }

        printf("%s\n", ans);

    }
    return 0;
}
