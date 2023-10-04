#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {

    ifstream cin("../a.in");
    ofstream cout("../a.out");

    string s, t;

    while (cin >> s >> t) {
        int j = 0;
        bool flag = true;
        for (int i = 0; i < s.size(); ++i) {
            while (t[j] != s[i] && j < t.size()) ++j;
            if (j == t.size()) {
                flag = false;
                break;
            }
            j++;
        }
        if (flag) cout << "Yes" << endl;
        else cout << "No" << endl;
    }

    return 0;
}