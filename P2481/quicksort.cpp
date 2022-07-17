#include <iostream>
#include "sort.h"


int main() {
    int arr[] = {25, 4, 6, 9, 10, 3, 1, 2, 7, 8};

    int len = sizeof(arr) / sizeof(arr[0]);
    sort(arr, 0, len - 1);
    for (int i = 0; i < len; ++i) {
        printf("%d ", arr[i]);
    }
}