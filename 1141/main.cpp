#include <iostream>
#include <string>

using namespace std;

bool match(char a, char b) {
    return a == '(' && b == ')' || a == '[' && b == ']';
}

string printStr(string &source, int pos[][100], int i, int j) {

    if (i > j)return "";
    if (i == j)
        return source[i] == '(' || source[i] == ')' ? "()" : "[]";

    if (pos[i][j] == -1)
        return source[i] + printStr(source, pos, i + 1, j - 1) + source[j];
    return printStr(source, pos, i, pos[i][j]) +
           printStr(source, pos, pos[i][j] + 1, j);
}

int main() {

    string source;
    // f[i][j] 表示i->j最小需要的括号数
    int i, j, f[100][100] = {0}, pos[100][100] = {0};
    cin >> source;

    int length = (int) source.size();

    // 初始化
    for (i = 0; i < length; ++i) f[i][i] = 1;

    for (int step = 1; step < length; ++step) {
        for (i = 0; i < length - step; ++i) {
            j = i + step;
            f[i][j] = length;
            if (match(source[i], source[j])) {
                f[i][j] = f[i + 1][j - 1];
                pos[i][j] = -1;
            }
            for (int k = i; k < j; ++k) {
                int temp = f[i][k] + f[k + 1][j];
                if (f[i][j] > temp) {
                    f[i][j] = temp;
                    pos[i][j] = k;
                }
            }
        }
    }

    cout << printStr(source, pos, 0, length - 1) << endl;

    return 0;
}