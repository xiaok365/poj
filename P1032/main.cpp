#include <iostream>
#include <fstream>

using namespace std;

int main() {

    ifstream cin("../a.in");
    ofstream cout("../a.out");

    int n, ans[1000];
    cin >> n;

    memset(ans, 0, 1000 * 4);

    int base = 2, j = 0;
    while (n >= base) {
        ans[j++] = base;
        n -= base;
        ++base;
    }

    while (n > 0) {
        int k = j - 1;
        while (n > 0 && k >= 0) {
            ans[k--] += 1;
            --n;
        }
    }

    for (int i = 0; i < j; ++i) {
        cout << ans[i] << " ";
    }
    cin.close();
    cout.close();

    return 0;
}