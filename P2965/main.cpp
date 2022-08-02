#include <iostream>
#include <algorithm>

using namespace std;

int origin[4][4] = {0}, map[4][4] = {0}, ans = 17, plan;

void init() {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            map[i][j] = origin[i][j];
        }
    }
}

void flip(int state) {
    int row = state / 4, column = state % 4;

    for (int i = 0; i < 4; ++i) {
        map[row][i] = !map[row][i];
    }

    for (int i = 0; i < 4; ++i) {
        map[i][column] = !map[i][column];
    }

    map[row][column] = !map[row][column];
}

bool find() {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (map[i][j] == 0) {
                return false;
            }
        }
    }
    return true;
}

int count_one(int n) {
    int total = 0;
    while (n > 0) {
        total++;
        n &= n - 1;
    }
    return total;
}

int main() {

    freopen("../a.in", "r", stdin);

    char ch[4];
    for (int i = 0; i < 4; ++i) {
        scanf("%s", ch);
        for (int j = 0; j < 4; ++j) {
            if (ch[j] == '-') {
                origin[i][j] = 1;
            }
        }
    }

    for (int i = 0; i < 65536; ++i) {
        int k = count_one(i);
        if (k > ans) {
            continue;
        }
        init();
        for (int j = 0; j < 16; ++j) {
            if (i >> j & 1) {
                flip(j);
            }
        }

        if (find()) {
            int tmp = ans;
            ans = min(ans, k);
            if (tmp != ans) {
                plan = i;
            }
        }
    }

    cout << ans << endl;
    for (int i = 1; i <= 4; ++i) {
        for (int j = 1; j <= 4; ++j) {
            if (plan & 1) {
                printf("%d %d\n", i, j);
            }
            plan >>= 1;
        }
    }

    return 0;
}