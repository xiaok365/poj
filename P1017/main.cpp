#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

struct Node {
    int product;
    int packet;
    int free;
};

Node a[6];

void init() {
    for (int i = 0; i < 6; ++i) {
        a[i].product = a[i].packet = a[i].free = 0;
    }
}

void pre(int key, int value) {
    switch (key) {
        case 5: {
            a[5].packet = value;
            break;
        }
        case 4: {
            a[4].packet = value;
            a[4].free = 11 * value;
            break;
        }
        case 3: {
            a[3].packet = value;
            a[3].free = 20 * value;
            break;
        }
        case 2: {
            a[2].packet = value / 4;
            if (value % 4 > 0) {
                a[2].free = 36 - 9 * (value % 4);
                a[2].packet++;
            }
            break;
        }
        case 1:
        case 0:
        default:
            break;
    }
}

int calc() {
    int sum = 0;
    for (int i = 0; i < 6; ++i) {
        sum += a[i].packet;
    }
    return sum;
}

int getSize3RealFree() {

    switch (a[2].free) {
        case 27:
            return 5 * 4;
        case 18:
            return 3 * 4;
        case 9:
            return 1 * 4;
        default:
            return 0;
    }
}

void putSize2() {

    if (a[1].product == 0) return;
    //放入size 4里面
    if (a[3].free > 0) {
        int real = min(a[1].product * 4, a[3].free);
        a[1].product -= real / 4;
        a[3].free -= real;
    }
    if (a[1].product == 0) return;
    // 放入size 3里面
    if (a[2].free > 0) {
        int real = min(a[1].product * 4, getSize3RealFree());
        a[1].product -= real / 4;
        a[2].free -= real;
    }
    if (a[1].product == 0) return;
    // size 2单独装箱
    a[1].packet = a[1].product / 9;
    if (a[1].product % 9 > 0) {
        a[1].packet++;
        a[1].free = 36 - (a[1].product % 9) * 4;
    }
}

void putSize1() {

    if (a[0].product == 0)return;
    int free = 0;
    for (int i = 1; i < 6; ++i) free += a[i].free;
    a[0].product -= min(free, a[0].product);
    if (a[0].product == 0)return;
    // size 1单独装箱
    a[0].packet = a[0].product / 36;
    if (a[0].product % 36 > 0) {
        a[0].packet++;
        a[0].free = 36 - a[0].product % 36;
    }
}

int main() {

    ifstream cin("../a.in");
    ofstream cout("../a.out");

    int sum = 1;

    while (sum > 0) {
        sum = 0;
        init();
        for (int i = 0; i < 6; ++i) {
            cin >> a[i].product;
            sum += a[i].product;
            pre(i, a[i].product);
        }
        putSize2();
        putSize1();
        if (sum == 0) break;
        cout << calc() << endl;
    }
    return 0;
}