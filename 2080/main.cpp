#include <iostream>

using namespace std;

const char week_str[][10] = {"Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
const int month_day[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

bool is_leap(int year) {
    if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0) {
        return true;
    }
    return false;
}

int days_of_year(int year) {
    return is_leap(year) ? 366 : 365;
}

int days_of_month(int year, int month) {

    if (is_leap(year) && month == 2) {
        return month_day[month - 1] + 1;
    }

    return month_day[month - 1];
}

int main() {

    freopen("../a.in", "r", stdin);

    int num;

    while (cin >> num && num != -1) {

        int year = 2000, month = 1, day = 1, week = num % 7;

        while (num >= days_of_year(year)) {
            num -= days_of_year(year);
            year++;
        }

        while (num >= days_of_month(year, month)) {
            num -= days_of_month(year, month);
            month++;
        }

        day += num;

        printf("%d-%.2d-%.2d %s\n", year, month, day, week_str[week]);
    }
    return 0;
}
