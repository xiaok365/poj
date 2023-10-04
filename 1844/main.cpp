#include <iostream>

using namespace std;

int find(int n) {

    int left, right, mid, sum;

    left = 1;
    right = 10000;

    while (left < right) {
        mid = (left + right) >> 1;
        sum = (1 + mid) * mid / 2;

        if (sum == n) {
            left = mid;
            break;
        } else if (sum < n) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }

    int surplus = (1 + left) * left / 2 - n;
    if (surplus & 1) {
        if (left & 1) return left + 2; else return left + 1;
    } else {
        return left;
    }
}

int main() {

    freopen("../a.in", "r", stdin);

    int n;
    cin >> n;
    printf("%d", find(n));

    return 0;
}
