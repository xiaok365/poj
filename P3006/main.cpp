#include <iostream>

using namespace std;

#define MAX_N 1000001
#define MAX_M 78497
bool num[MAX_N] = {false};
int prime[MAX_M], prime_cnt = 0;

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

int main() {

    freopen("../a.in", "r", stdin);

    get_prime();
    num[0] = num[1] = true;

    int a, b, n;

    while (cin >> a >> b >> n && !(a == 0 && b == 0 && n == 0)) {
        for (int i = 0; a + b * i < MAX_N; ++i) {
            if (!num[a + b * i]) {
                n--;
            }
            if (n == 0) {
                cout << a + b * i << endl;
                break;
            }
        }
    }
    return 0;
}