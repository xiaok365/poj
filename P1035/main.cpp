#include <iostream>
#include <fstream>
#include <string>

using namespace std;
int n = 0;

string word[10000];

bool matchReplace(string &a, string &b) {

    int i, diff = 0;
    for (i = 0; i < a.size(); ++i) {
        if (a[i] != b[i]) diff++;
    }
    return diff <= 1;
}

bool deleteAndInsert(string &a, string &b) {

    string tmp, ta, tb;
    if (a.size() > b.size()) {
        ta = b;
        tb = a;
    } else {
        ta = a;
        tb = b;
    }
    unsigned long i;
    for (i = 0; i < tb.size(); ++i) {
        tmp = tb;
        if (tmp.erase(i, 1) == ta) {
            return true;
        }
    }
    return false;
}

void process(string &st, ofstream &cout) {

    int i, tot = 0;
    long la = st.size(), lb;

    string ans[10000];

    for (i = 0; i < n; ++i) {
        string t = word[i];
        lb = word[i].size();
        if (((la - lb) > 1)
            || ((la - lb) < -1)) {
            continue;
        }
        if (word[i] == st) {
            cout << st << " is correct" << endl;
            return;
        }
        if (word[i].size() == st.size()) {
            if (matchReplace(word[i], st))
                ans[tot++] = word[i];
        } else if (deleteAndInsert(word[i], st)) {
            ans[tot++] = word[i];
        }
    }
    cout << st << ":";
    for (i = 0; i < tot; ++i) cout << " " << ans[i];
    cout << endl;
}

int main() {

    ifstream cin("../a.in");
    ofstream cout("../a.out");

    string st;
    while (cin >> st && st != "#") {
        word[n++] = st;
    }
    while (cin >> st && st != "#") {
        process(st, cout);
    }
    return 0;
}