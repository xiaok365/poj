#include <iostream>
#include <fstream>
#include <string>

using namespace std;
string monthHaab[19], dayTzolkin[20];

void init() {
    monthHaab[0] = "pop";
    monthHaab[1] = "no";
    monthHaab[2] = "zip";
    monthHaab[3] = "zotz";
    monthHaab[4] = "tzec";
    monthHaab[5] = "xul";
    monthHaab[6] = "yoxkin";
    monthHaab[7] = "mol";
    monthHaab[8] = "chen";
    monthHaab[9] = "yax";
    monthHaab[10] = "zac";
    monthHaab[11] = "ceh";
    monthHaab[12] = "mac";
    monthHaab[13] = "kankin";
    monthHaab[14] = "muan";
    monthHaab[15] = "pax";
    monthHaab[16] = "koyab";
    monthHaab[17] = "cumhu";
    monthHaab[18] = "uayet";

    dayTzolkin[0] = "imix";
    dayTzolkin[1] = "ik";
    dayTzolkin[2] = "akbal";
    dayTzolkin[3] = "kan";
    dayTzolkin[4] = "chicchan";
    dayTzolkin[5] = "cimi";
    dayTzolkin[6] = "manik";
    dayTzolkin[7] = "lamat";
    dayTzolkin[8] = "muluk";
    dayTzolkin[9] = "ok";
    dayTzolkin[10] = "chuen";
    dayTzolkin[11] = "eb";
    dayTzolkin[12] = "ben";
    dayTzolkin[13] = "ix";
    dayTzolkin[14] = "mem";
    dayTzolkin[15] = "cib";
    dayTzolkin[16] = "caban";
    dayTzolkin[17] = "eznab";
    dayTzolkin[18] = "canac";
    dayTzolkin[19] = "ahau";
}

int getMonthNumber(const string &month) {
    for (int i = 0; i < 19; ++i) {
        if (monthHaab[i] == month) {
            return i;
        }
    }
    return 0;
}

int sumDayOfMonth(const string &month) {

    int monthNumber = getMonthNumber(month);
    return monthNumber * 20;
}

int main() {

    ifstream cin("../a.in");
    ofstream cout("../a.out");

    int n, day, year;
    string month;

    init();

    cin >> n;
    cout << n << endl;
    for (int i = 0; i < n; ++i) {
        char ch;
        cin >> day >> ch >> month >> year;
        if (ch != '.') month = ch + month;
        int total = year * 365 + sumDayOfMonth(month) + day;
        int tDay = total % 260;
        cout << tDay % 13 + 1 << " " << dayTzolkin[tDay % 20] << " " << total / 260 << endl;
    }

    return 0;
}