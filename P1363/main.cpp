#include <iostream>
#include <fstream>

using namespace std;

int main() {

    ifstream cin("../a.in");
    ofstream cout("../a.out");

    int n, a[1000];
    bool first = true;
    while (cin >> n && n != 0) {

        if (first) {
            first = false;
        } else {
            cout << endl;
        }
        cin >> a[0];
        while (a[0] != 0) {
            for (int i = 1; i < n; ++i) cin >> a[i];

            int outNo = 0, inNo = 1, stack[1000] = {0}, stackSize = 0;
            bool flag = true;
            while (flag && outNo < n) {
                // 要出栈的编号小于栈顶，直接不可达
                if (stackSize > 0 && a[outNo] < stack[stackSize - 1]) {
                    flag = false;
                    continue;
                }
                // 出栈
                if (stackSize > 0 && stack[stackSize - 1] == a[outNo]) {
                    outNo++;
                    stackSize--;
                } else {
                    while (inNo != a[outNo] && inNo <= n) {
                        stack[stackSize++] = inNo;
                        inNo++;
                    }
                    if (inNo == a[outNo]) {
                        inNo++;
                        outNo++;
                    } else {
                        flag = false;
                    }
                }
            }

            if (outNo == n)cout << "Yes" << endl;
            else cout << "No" << endl;

            cin >> a[0];
        }
    }

    return 0;
}