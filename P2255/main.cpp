#include <iostream>
#include <string>

using namespace std;

string st1, st2;

// 截取子串
void solve1(string a, string b) {
    if (a.size() == 0) return;

    int pos = b.find(a[0]);

    solve1(a.substr(1, pos), b.substr(0, pos));
    solve1(a.substr(pos + 1), b.substr(pos + 1));
    cout << a[0];
}

// 记录下标
void solve(int x1, int x2, int y1, int y2) {
    if (x1 > x2) return;

    int pos = st2.find(st1[x1]);
    int left = pos - y1;

    solve(x1 + 1, x1 + left, y1, pos - 1);
    solve(x1 + left + 1, x2, pos + 1, y2);
    cout << st1[x1];
}

int main() {

    freopen("../a.in", "r", stdin);

    while (cin >> st1 >> st2) {
        solve(0, st1.size() - 1, 0, st2.size() - 1);
        cout << endl;
//        solve1(st1, st2);
//        cout << endl;
    }

    return 0;
}
