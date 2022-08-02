#include <iostream>

using namespace std;

#define MAX_N 10001
#define MAX_M 1229
bool num[MAX_N] = {false};
int prime[MAX_M], prime_cnt = 0, ans[MAX_N] = {0};

void get_prime() {
    for (int i = 2; i <= MAX_N; i++) {
        if (!num[i]) {
            prime[prime_cnt++] = i;
        }
        for (int j = 0; j < prime_cnt && i * prime[j] <= MAX_N; ++j) {
            num[i * prime[j]] = true;
            if (i % prime[j] == 0) break;
        }
    }
}

void solve() {

    get_prime();

    for (int i = 0; i < prime_cnt; ++i) {
        int j = i, t = prime[i];
        while (t <= MAX_N) {
            ans[t]++;
            t += prime[++j];
        }
    }
}

int main() {

    freopen("../a.in", "r", stdin);

    solve();

    int n;
    while (scanf("%d", &n) > 0 && n != 0) {
        printf("%d\n", ans[n]);
    }

    return 0;
}
