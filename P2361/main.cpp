#include <iostream>

using namespace std;

char map[3][4];
int cnt_x, cnt_o;

bool is_win(char ch) {

    for (int i = 0; i < 3; ++i) {

        int j;
        // 每一行
        for (j = 0; j < 3; ++j) if (map[i][j] != ch) break;
        if (j == 3) return true;

        // 每一列
        for (j = 0; j < 3; ++j) if (map[j][i] != ch) break;
        if (j == 3) return true;
    }

    if (map[0][0] == ch && map[1][1] == ch && map[2][2] == ch) return true;
    if (map[0][2] == ch && map[1][1] == ch && map[2][0] == ch) return true;

    return false;
}

bool process() {

    if (abs(cnt_x - cnt_o) > 1) return false;

    if (cnt_o > cnt_x) return false;

    if (cnt_x == cnt_o && !is_win('X')) return true;

    if (cnt_x == cnt_o + 1 && !is_win('O')) return true;

    return false;
}

int main() {

    freopen("../a.in", "r", stdin);

    int n;

    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {

        cnt_x = 0, cnt_o = 0;

        for (int j = 0; j < 3; ++j) {
            scanf("%s", map[j]);

            // 统计数量
            for (int k = 0; k < 3; ++k) {
                if (map[j][k] == 'X') {
                    cnt_x++;
                } else if (map[j][k] == 'O') {
                    cnt_o++;
                }
            }
        }
        if (process()) printf("yes\n"); else printf("no\n");
    }
    return 0;
}
