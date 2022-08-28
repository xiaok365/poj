#include <iostream>
#include <cstring>

int a[10], cnt[10] = {0}, ans, seq[10];
char str[10][6] = {"ABDE", "ABC", "BCEF", "ADG", "BDEFH", "CFI", "DEGH", "GHI", "EFHI"};

void add(int step, int x, int arr[]) {
    for (int i = 0; i < strlen(str[step]); ++i) {
        arr[str[step][i] - 'A'] += x;
    }
}

bool valid(const int arr[]) {
    for (int i = 0; i < 9; ++i) {
        if (arr[i] % 4 != 0) {
            return false;
        }
    }
    return true;
}

void dfs(int step) {
    if (step == 9) {
        int b[10], tot = 0;
        memcpy(b, a, 36);
        for (int i = 0; i < 9; ++i) {
            add(i, cnt[i], b);
            tot += cnt[i];
        }
        if (valid(b) && tot < ans) {
            ans = tot;
            memcpy(seq, cnt, 36);
        }
        return;
    }
    for (int i = 0; i < 4; ++i) {
        cnt[step] = i;
        dfs(step + 1);
    }
}

int main() {
    freopen("../a.in", "r", stdin);

    for (int i = 0; i < 9; ++i) {
        scanf("%d", &a[i]);
        cnt[i] = 0;
    }
    ans = 0x7fffffff;
    dfs(0);
    for (int i = 0; i < 9; ++i) {
        while (seq[i] > 0) {
            printf("%d ", i + 1);
            seq[i]--;
        }
    }

    return 0;
}
