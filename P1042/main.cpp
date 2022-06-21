#include <iostream>
#include <fstream>

using namespace std;

int n, h, f[25] = {0}, d[25] = {0}, t[25] = {0};

void solve(int end, int &maxFish, int ans[]) {
    int total = 0, used[25] = {0};

    int time = h;
    for (int i = 0; i < end; ++i) time -= t[i];

    while (time > 0) {
        int j = 0, round = -1;

        for (int i = 0; i <= end; ++i) {
            int temp = f[i] - d[i] * used[i];
            if (temp < 0) temp = 0;
            if (temp > round) {
                round = temp;
                j = i;
            }
        }
        used[j]++;
        total += round;
        time--;
    }
    if (total > maxFish) {
        maxFish = total;
        for (int i = 0; i < n; ++i) ans[i] = used[i];
    }
}

int main() {

    ifstream cin("../a.in");
    ofstream cout("../a.out");

    while (cin >> n && n > 0) {
        cin >> h;
        h = h * 12;
        for (int i = 0; i < n; ++i) cin >> f[i];
        for (int i = 0; i < n; ++i) cin >> d[i];
        for (int i = 0; i < n - 1; ++i) cin >> t[i];
        int maxFish = 0x80000000, ans[25] = {0};

        for (int i = 0; i < n; ++i) solve(i, maxFish, ans);

        cout << ans[0] * 5;
        for (int i = 1; i < n; ++i) cout << ", " << ans[i] * 5;
        cout << endl;
        cout << "Number of fish expected: " << maxFish << endl << endl;
    }

    return 0;
}