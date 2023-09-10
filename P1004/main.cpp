// Copyright 2016 Kyle Wilson
#include <iostream>
using std::cin;
using std::cout;

int main() {
  freopen("../a.in", "r", stdin);
  freopen("../a.out", "w", stdout);

  double sum = 0, s;

  for (int i = 0; i < 12; ++i) {
    cin >> s;
    sum += s;
  }

  cout << "$" << sum / 12 << std::endl;
  return 0;
}
