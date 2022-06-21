#include <iostream>
#include <fstream>
#include <cstdio>

using namespace std;

const int MAXN = 31269;
unsigned int sum[MAXN] = {0}, len[MAXN] = {0};

long singCycle(long n) {

    long i = 0, step = 1, cycle = 0, k = 10;
    while (i < n) {
        cycle++;
        if (cycle == k) {
            step++;
            k *= 10;
        }
        i += step;
    }
    long left = n - (i - step);

    char st[11];
    sprintf(st, "%ld", cycle);
    return st[left - 1] - '0';
}

long solve(long n) {

    long step = 1, cycle = 0, j = 0, i = 0, k = 10;
    while (i < n) {
        cycle++;
        if (cycle == k) {
            step++;
            k *= 10;
        }
        j = j + step;
        i += j;
    }

    long left = n - (i - j);

    return singCycle(left);
}

int getLen(int n) {
    int total = 0;
    while (n > 0) {
        total++;
        n /= 10;
    }
    return total;
}

void init() {
    for (int i = 1; i < MAXN; ++i) {
        len[i] += len[i - 1] + getLen(i);
        sum[i] += sum[i - 1] + len[i];
    }
}

int findSum(int n) {

    int left = 1, right = MAXN - 1, mid;
    while (left < right) {
        mid = (left + right) >> 1;

        if (sum[mid] == n) {
            return n - sum[mid - 1];
        } else if (sum[mid] < n) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return n - sum[left - 1];
}

int findLen(int n) {
    int left = 1, right = MAXN - 1, mid;
    while (left < right) {
        mid = (left + right) >> 1;

        if (len[mid] < n) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    char st[11];
    sprintf(st, "%d", left);
    return st[n - len[left - 1] - 1] - '0';
}

int main() {

    ifstream cin("../a.in");
    ofstream cout("../a.out");

    unsigned int t, n;

    init();
    cin >> t;
    while (t--) {
        cin >> n;
//        cout << solve(n) << endl;  循环模拟
        cout << findLen(findSum(n)) << endl;
    }
    return 0;
}