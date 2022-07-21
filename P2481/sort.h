#ifndef P2481_SORT_H
#define P2481_SORT_H

#include <cstdlib>
#include <ctime>
#include <random>

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
//    random_device rd;
//    default_random_engine eng(rd());
//    uniform_int_distribution<int> distr(left, right);
//
//    int pivot = distr(eng);
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

#endif //P2481_SORT_H
