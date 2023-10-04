#include <iostream>
#include <fstream>

using namespace std;

// 0:有环 1:无序 2:成功
int topologySort(bool map[][26], const int inDegree[], const bool visit[], int n, char ans[]) {

    int tempInDegree[26];
    bool tempVisit[26], fail = false;
    for (int i = 0; i < 26; ++i) {
        tempInDegree[i] = inDegree[i];
        tempVisit[i] = visit[i];
    }
    for (int i = 0; i < n; ++i) {
        int start = -1, zeroCnt = 0;
        bool flag = false;
        for (int j = 0; j < n; ++j) {
            if (tempVisit[j]) {
                flag = true;
                if (tempInDegree[j] == 0) {
                    zeroCnt++;
                    start = j;
                }
            }
        }

        // 有环，有点，但没有入度为0的点
        if (flag && zeroCnt == 0) {
            return 0;
        }
        // 没有入度为0的点
        if (zeroCnt == 0) {
            return 2;
        }

        // 多个入度为0的点
        if (zeroCnt > 1) {
            fail = true;
        }

        ans[i] = char(start + 'A');
        tempVisit[start] = false;
        for (int k = 0; k < n; ++k) {
            if (map[start][k]) {
                tempInDegree[k]--;
            }
        }
    }

    if (fail) return 2;
    else return 1;
}

int main() {

    ifstream cin("../a.in");
    ofstream cout("../a.out");

    int n, m, inDegree[26];
    bool map[26][26], visit[26];

    while (cin >> n >> m && n > 0) {

        memset(inDegree, 0, 26 * 4);
        memset(map, false, 26 * 26);
        memset(visit, false, 26);

        char a, p, b;
        bool success = false, conflict = false;
        for (int i = 0; i < m; ++i) {
            cin >> a >> p >> b;
            //已经有序，或者有冲突，直接跳过
            if (success || conflict) continue;
            if (map[a - 'A'][b - 'A']) continue;

            map[a - 'A'][b - 'A'] = true;
            visit[a - 'A'] = visit[b - 'A'] = true;
            inDegree[b - 'A']++;

            char ans[26] = {0};
            int ret = topologySort(map, inDegree, visit, n, ans);

            switch (ret) {
                case 0:
                    conflict = true;
                    cout << "Inconsistency found after " << i + 1 << " relations." << endl;
                    break;
                case 1:
                    success = true;
                    cout << "Sorted sequence determined after " << i + 1 << " relations: ";
                    for (int j = 0; j < n; ++j) cout << ans[j];
                    cout << "." << endl;
                    break;
                default:
                    break;
            }
        }

        // 无序
        if (!success && !conflict) {
            cout << "Sorted sequence cannot be determined." << endl;
        }
    }

    return 0;
}