#include <iostream>
#include <cmath>

using namespace std;
double t, d, h;
bool a[3];


void get_t() {
    double e = 6.11 * exp(5417.7530 * ((1 / 273.16) - (1 / (d + 273.16))));
    t = h - 0.5555 * (e - 10.0);
}

void get_d() {
    double e = (h - t) / 0.5555 + 10.0;
    d = 1 / (1 / 273.16 - log(e / 6.11) / 5417.7530) - 273.16;
}

void get_h() {
    double e = 6.11 * pow(2.718281828, 5417.7530 * ((1 / 273.16) - (1 / (d + 273.16))));
    h = 0.5555 * (e - 10.0) + t;
}

void set(char ch, double value) {
    switch (ch) {
        case 'T':
            a[0] = true;
            t = value;
            break;
        case 'D':
            a[1] = true;
            d = value;
            break;
        case 'H':
            a[2] = true;
            h = value;
            break;
        default:
            break;
    }
}

void calc() {
    if (!a[0]) {
        get_t();
    } else if (!a[1]) {
        get_d();
    } else {
        get_h();
    }
}

int main() {
    freopen("../a.in", "r", stdin);

    char ch;
    double value;

    cin >> ch;

    while (ch != 'E') {
        a[0] = a[1] = a[2] = false;
        t = d = h = 0.0;
        cin >> value;
        set(ch, value);
        cin >> ch;
        cin >> value;
        set(ch, value);
        calc();
        printf("T %.1lf D %.1lf H %.1lf\n", t, d, h);
        cin >> ch;
    }

    return 0;
}