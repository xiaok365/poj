#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string getZeroString(long n) {

    string st;
    for (int i = 0; i < n; ++i) st += '0';
    return st;
}

string multiply(const string &a, const string &b) {

    long l1 = a.size() - 1;
    long l2 = b.size() - 1;

    long l = l1 + l2 + 1;
    int *ret = new int[l + 1];
    for (int i = 0; i < l + 1; ++i) ret[i] = 0;

    for (long i = l1; i >= 0; --i)
        for (long j = l2; j >= 0; --j) {

            long pos = l1 - i + l2 - j;
            int temp = (a[i] - 48) * (b[j] - 48) + ret[pos];

            ret[pos] = temp % 10;
            ret[pos + 1] += temp / 10;
        }

    if (ret[l] <= 0) { --l; };

    string st;
    for (long i = l; i >= 0; --i) {
        st += ret[i] + '0';
    }

    delete[]ret;
    return st;
}

string exp(string st, int n) {

    unsigned long dot = st.find('.');
    unsigned long front = 0, end = 0;
    //如果为小数，去掉末尾的0和小数点
    if (dot >= 0) {
        end = st.size() - 1;
        while (end > 0) {
            if (st[end] != '0')break;
            --end;
        }
        st.erase(end + 1, st.size() - end);
        //去掉.
        st.erase(dot, 1);
    }

    // 计算小数部分的数字长度
    long decimalSize;
    if (dot < 0) decimalSize = 0;
    else decimalSize = (st.size() - dot) * n;

    //去掉前面的0
    while (front < st.size()) {
        if (st[front] != '0' && st[front] != '.')break;
        ++front;
    }
    string original = st.substr(front, st.size());
    string answer = original;

    //如果全是0，字符串为空，直接返回0
    if (original.empty()) { return "0"; }

    for (int i = 0; i < n - 1; ++i) {
        answer = multiply(answer, original);
    }

    //没有小数部分
    if (dot < 0 || decimalSize == 0) return answer;

    //整数为0,  如0.000123
    if (answer.size() <= decimalSize) {
        return "." + getZeroString(decimalSize - answer.size()) + answer;
    }

    //正常小数位， 如123.1
    answer.insert(answer.size() - decimalSize, ".");

    return answer;
}

int main() {

    ifstream cin("../a.in");
    ofstream cout("../a.out");

    string r;
    int n;

    while (cin >> r >> n) {
        if (n == 0) cout << 1 << endl;
        else
            cout << exp(r, n) << endl;
    }

    cin.close();
    cout.close();
    return 0;
}