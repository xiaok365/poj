#include <iostream>
#include <cmath>

using namespace std;

int main() {

    freopen("../a.in", "r", stdin);
    double n, p;
    while (~scanf("%lf%lf", &n, &p)) {
        printf("%.0lf\n", pow(p, 1 / n));
    }
    return 0;
}
