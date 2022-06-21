#include <iostream>
#include <fstream>

using namespace std;

int prim(int a[][100], int n) {

    bool visit[100] = {false};
    int set[100], total = 1, ans = 0;
    set[0] = 0;
    visit[0] = true;

    while (total < n) {

        int nextNode = 0, maxDis = 0x7fffffff;
        for (int i = 0; i < total; ++i) {
            for (int j = 0; j < n; ++j) {
                if (!visit[j] && a[set[i]][j] < maxDis) {
                    maxDis = a[set[i]][j];
                    nextNode = j;
                }
            }
        }
        ans += maxDis;
        set[total++] = nextNode;
        visit[nextNode] = true;
    }

    return ans;
}

int main() {

    ifstream cin("../a.in");
    ofstream cout("../a.out");

    int n, a[100][100];

    while (cin >> n) {

        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j) cin >> a[i][j];

        cout << prim(a, n) << endl;
    }

    return 0;
}