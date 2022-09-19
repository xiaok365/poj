#include <iostream>
#include <string>
#include <map>

using namespace std;

string to_str(int d) {
    string ret;
    if (d == 0) return "0";
    while (d) {
        int t = d % 10;
        ret = (char) (t + '0') + ret;
        d /= 10;
    }
    return ret;
}

string convert(string &st) {
    int a[11] = {0};
    for (int i = 0; i < st.size(); ++i) {
        a[st[i] - '0']++;
    }
    string ret;
    for (int i = 0; i < 10; ++i) {
        if (a[i] > 0) {
            ret += to_str(a[i]) + to_str(i);
        }
    }
    return ret;
}

void solve(string &st) {
    map<string, int> st_map;

    string last = st;
    for (int i = 1; i <= 15; ++i) {
        string cur = convert(last);
        if (cur == last) {
            if (i == 1) {
                cout << st << " is self-inventorying\n";
                return;
            } else {
                cout << st << " is self-inventorying after " << i - 1 << " steps\n";
                return;
            }
        }

        map<string, int>::iterator iter;
        iter = st_map.find(cur);
        if (iter != st_map.end()) {
            cout << st << " enters an inventory loop of length " << i - iter->second << endl;
            return;
        }

        st_map[cur] = i, last = cur;
    }

    cout << st << " can not be classified after 15 iterations\n";
}

int main() {

    freopen("../a.in", "r", stdin);

    string st;

    while (cin >> st && st != "-1") {
        solve(st);
    }
    return 0;
}
