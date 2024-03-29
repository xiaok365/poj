#include <iostream>

using namespace std;

#define MAX_N 32768
#define MAX_M 3512
bool num[MAX_N] = {false};
int prime[MAX_M], cnt = 0;

void get_prime() {
    for (int i = 2; i <= MAX_N; i++) {
        if (!num[i]) {
            prime[cnt++] = i;
        }
        for (int j = 0; j < cnt && i * prime[j] <= MAX_N; ++j) {
            num[i * prime[j]] = true;
            if (i % prime[j] == 0) break;
        }
    }

}

int main() {

    freopen("../a.in", "r", stdin);
    get_prime();

    int n;
    while (scanf("%d", &n) && n != 0) {

        int ans = 0;
        for (int i = 1; i < cnt && prime[i] <= n / 2; ++i) {
            if (!num[n - prime[i]]) {
                ans++;
            }
        }
        printf("%d\n", ans);
    }

    return 0;
}
