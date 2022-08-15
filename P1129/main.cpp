#include <iostream>
#include <set>

using namespace std;

#define  MAX_N 26
bool map[MAX_N][MAX_N];
int n, ans;

void bron_kerbosch(set<int> &r, set<int> &p, set<int> &x) {

    if (p.empty() && x.empty()) {
//        set<int>::iterator it = r.begin();
//        while (it != r.end()) {
//            printf("%d ", (*it));
//            it++;
//        }
//        printf("\n");

        if (r.size() > ans) ans = r.size();
    }

    int pivot = *(p.begin());

    // 枚举所有点
    for (int v = 0; v < n; ++v) {

        if (p.find(v) == p.end() || map[pivot][v]) continue;

        set<int> p1, x1;

        for (set<int>::iterator it1 = p.begin(); it1 != p.end(); ++it1) {
            if (map[v][*it1]) p1.insert(*it1);
        }

        for (set<int>::iterator it1 = x.begin(); it1 != x.end(); ++it1) {
            if (map[v][*it1]) x1.insert(*it1);
        }

        r.insert(v);
        bron_kerbosch(r, p1, x1);
        r.erase(v);
        p.erase(v);
        x.insert(v);
    }
}


int main() {

    freopen("../a.in", "r", stdin);

    char st[MAX_N + 2];

    while (scanf("%d", &n) && n != 0) {
        memset(map, false, sizeof map);
        for (int i = 0; i < n; ++i) {
            scanf("%s", st);
            for (int j = 2; st[j] != '\0'; ++j) {
                map[st[0] - 'A'][st[j] - 'A'] = map[st[j] - 'A'][st[0] - 'A'] = true;
            }
        }

        set<int> r, p, x;

        for (int i = 0; i < n; ++i) p.insert(i);
        ans = 0;
        bron_kerbosch(r, p, x);
        if (ans == 1) printf("%d channel needed.\n", ans);
        else printf("%d channels needed.\n", ans);
    }

    return 0;
}
