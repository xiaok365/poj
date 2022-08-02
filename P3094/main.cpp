#include <iostream>
#include <string>

using namespace std;

int main() {

    freopen("../a.in", "r", stdin);

    string st;

    getline(cin, st);
    while (st[0] != '#') {
        int t = 0;
        for (int i = 0; i < st.size(); ++i) {

            if (st[i] != ' ') {
                t += (st[i] - 64) * (i + 1);
            }
        }
        cout << t << endl;
        getline(cin, st);
    }
    return 0;
}