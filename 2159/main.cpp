#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

template<typename T>
void swap(T arr[], int s, int t) {
    T temp = arr[s];
    arr[s] = arr[t];
    arr[t] = temp;
}

template<typename T>
int partition(T arr[], int left, int right) {

    srand(time(0));
    int pivot = left + rand() % (right - left + 1);
    swap(arr, left, pivot);

    T base = arr[left];

    while (left < right) {
        while (left < right && base <= arr[right]) right--;
        arr[left] = arr[right];
        while (left < right && arr[left] <= base) left++;
        arr[right] = arr[left];
    }
    arr[left] = base;

    return left;
}

template<typename T>
void sort(T arr[], int start, int end) {
    if (start >= end) {
        return;
    }
    int index = partition(arr, start, end);
    sort(arr, start, index - 1);
    sort(arr, index + 1, end);
}

int main() {
    freopen("../a.in", "r", stdin);

    int a[26] = {0}, b[26] = {0};
    string st;

    cin >> st;
    for (int i = 0; i < st.size(); ++i) {
        a[st[i] - 'A']++;
    }

    cin >> st;
    for (int i = 0; i < st.size(); ++i) {
        b[st[i] - 'A']++;
    }

    sort(a, 0, 25);
    sort(b, 0, 25);

    bool can = true;
    for (int i = 0; i < 26; ++i) {
        if (a[i] != b[i]) {
            can = false;
            break;
        }
    }

    if (can) cout << "YES"; else cout << "NO";

    return 0;
}
