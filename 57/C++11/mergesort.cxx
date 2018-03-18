#include <algorithm>
#include <iostream>
#include <iomanip>
#include <functional>
#include <cmath>

using namespace std;

void printVector(vector<int>::iterator b, vector<int>::iterator e) {
  cout << "v:";
  for (auto i = b; i != e; i++) {
    cout << " " << setfill(' ') << setw(2) << *i;
  }
  cout << "\n";
}

void mergeSort(vector<int>::iterator b, vector<int>::iterator e) {
  if(e - b > 1) {
    auto pivot = b + distance(b, e) / 2;
    mergeSort(b, pivot);
    mergeSort(pivot, e);
    inplace_merge(b, pivot, e);
  }
}

int main() {
  cout << "Modern C++11 merge sort." << endl;
  vector<int> v(20);
  auto randomize = bind(
    uniform_int_distribution<>{0, 99},
    default_random_engine{});
  generate(v.begin(), v.end(), randomize);
  printVector(v.begin(), v.end());
  mergeSort(v.begin(), v.end());
  printVector(v.begin(), v.end());
}
