#include <iostream>
#include <fstream>

using namespace std;

long exGcg(long long a, long long b, long long &x, long long &y) {

    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }

    long long c = exGcg(b, a % b, x, y);
    long long temp = x;
    x = y;
    y = temp - a / b * y;
    return c;
}

int main() {

    ifstream cin("../a.in");
    ofstream cout("../a.out");

    long long x, y, m, n, l;
    cin >> x >> y >> m >> n >> l;

    long long a = m - n, b = l, c = y - x, x1, y1;

    // a*x+b*y=c,  b一定为正数，把a变成正数，求出的d才是正数
    if (a < 0) {
        a = -a;
        c = -c;
    }

    long long d = exGcg(a, b, x1, y1);

    // 求方程的整数解 (m-n)*x1+l*y1=d,方程的通解为x=x1+k*b, y=y1-k*a;

    if (c % d == 0) {
        //原方程为(m-n)*x1+l*y1=y-x,求得的解需要乘以(y-x)/d
        x1 = x1 * c / d;
        // 最小解是方程左右除以d，即a1*x1+b1*y1=k(k=(y-x)/d), a1=a/d, b1=b/d
        long long b1 = b / d;
        // 对b1先取模，再加b1是为了把负数变为正数
        x1 = (x1 % b1 + b1) % b1;
        cout << x1 << endl;
    } else {
        cout << "Impossible" << endl;
    }

    cin.close();
    cout.close();

    return 0;
}