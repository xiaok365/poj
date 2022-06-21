#include <iostream>
#include <fstream>

using namespace std;

struct StackNode {
    int value;
    int merge;
};

void push(StackNode *stack, int &stackSize, int value) {

    stack[stackSize].value = value;
    stackSize++;
}

void pop(StackNode *stack, int &stackSize, int *ans, int index) {

    while (stackSize > 0 && stack[stackSize - 1].value <= 0) {

        if (stackSize > 1) {
            stack[stackSize - 2].merge += stack[stackSize - 1].merge;
            stack[stackSize - 1].merge = 1;
        }
        stackSize--;
    }

    stack[stackSize - 1].value--;
    ans[index] = stack[stackSize - 1].merge;
}

void init(StackNode *stack, int &stackSize, int *ans, int n) {

    stackSize = 0;
    for (int i = 0; i < 20; ++i) {
        stack[i].value = ans[i] = 0;
        stack[i].merge = 1;
    }
}

int main() {

    ifstream cin("../a.in");
    ofstream cout("../a.out");

    int t, n, stackSize, data;
    StackNode stack[20];
    int ans[20];
    cin >> t;
    for (int i = 0; i < t; ++i) {
        cin >> n;
        int total = 0;
        init(stack, stackSize, ans, n);
        // each case
        for (int j = 0; j < n; ++j) {
            cin >> data;
            data -= total;
            total += data;
            push(stack, stackSize, data);
            pop(stack, stackSize, ans, j);
        }

        for (int k = 0; k < n; ++k) {
            cout << ans[k] << " ";
        }
        cout << endl;
    }
    return 0;
}