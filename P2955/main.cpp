#include <iostream>

using namespace std;

#define MAX_N 101

bool match(char s, char t) {
    return s == '(' && t == ')' || s == '[' && t == ']';
}

int main() {

    freopen("../a.in", "r", stdin);

    char st[MAX_N];

    while (scanf("%s", st) && st[0] != 'e') {

        int dp[MAX_N][MAX_N] = {0}, len = strlen(st);

        for (int d = 1; d <= len; ++d) {
            for (int i = 0; i <= len - d; ++i) {
                int j = i + d - 1;
                if (match(st[i], st[j])) {
                    dp[i][j] = max(dp[i][j], dp[i + 1][j - 1] + 2);
                }
                for (int k = i; k < j; ++k) {
                    dp[i][j] = max(dp[i][j], dp[i][k] + dp[k + 1][j]);
                }
            }
        }

        printf("%d\n", dp[0][len - 1]);
    }
    return 0;
}
