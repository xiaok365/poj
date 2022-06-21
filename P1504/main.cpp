#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void trimZero(string &st) {
    int i = 0;
    while (st[i] == '0') i++;
    st = st.substr(i, st.size());
}

void add(string &a, string &b) {

    trimZero(a);
    trimZero(b);

    int c[100] = {0};

    int len = max(a.size(), b.size());
    for (int i = 0; i < len; ++i) {
        if (i < a.size()) {
            c[i] += a[i] - '0';
        }
        if (i < b.size()) {
            c[i] += b[i] - '0';
        }
        c[i + 1] += c[i] / 10;
        c[i] %= 10;
    }

    int start = 0, end = len;
    while (c[start] == 0) ++start;
    while (c[end] == 0) --end;
    for (int i = start; i <= end; ++i) cout << c[i];
    if (start > end) cout << 0 << endl;
    else cout << endl;
}

int main() {

    ifstream cin("../a.in");
    ofstream cout("../a.out");

    int t;
    string a, b;
    cin >> t;
    while (t--) {
        cin >> a >> b;
        add(a, b);
    }
    return 0;
}