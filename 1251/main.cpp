#include <iostream>
#include <fstream>

using namespace std;

void init(int map[][26]) {
    memset(map, -1, 26 * 26 * 4);
}

int prim(int map[][26], int n) {
    bool visit[26] = {false};
    int ans = 0;
    visit[0] = true;
    for (int i = 0; i < n - 1; ++i) {
        int minCost = 0x7fffff, point = 0;
        for (int j = 0; j < n; ++j) {
            if (visit[j]) {
                for (int k = 0; k < n; ++k) {
                    if (!visit[k] && map[j][k] != -1 && map[j][k] < minCost) {
                        minCost = map[j][k];
                        point = k;
                    }
                }
            }
        }
        visit[point] = true;
        ans += minCost;
    }
    return ans;
}

int main() {

    ifstream cin("../a.in");
    ofstream cout("../a.out");

    int n, map[26][26], cost;
    while (cin >> n && n > 0) {
        init(map);
        for (int i = 0; i < n - 1; ++i) {
            char from, to;
            int m;
            cin >> from >> m;
            while (m--) {
                cin >> to >> cost;
                map[from - 'A'][to - 'A'] = map[to - 'A'][from - 'A'] = cost;

            }
        }
        cout << prim(map, n) << endl;
    }
    return 0;
}