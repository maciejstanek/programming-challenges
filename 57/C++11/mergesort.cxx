#include <algorithm>
#include <iostream>
#include <iomanip>
#include <functional>

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
  srand(time(0));
  generate(v.begin(), v.end(), [](){return rand()%100;});
  printVector(v.begin(), v.end());
  mergeSort(v.begin(), v.end());
  printVector(v.begin(), v.end());
}
