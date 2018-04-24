#include <random>
#include <iostream>
#include <iterator>
#include <algorithm>

void f(std::vector<int>& v) {
  // Fill this function so that the vector v will be sorted {{{
  // }}}
}
 

int main()
{
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(1, 8);
  std::vector<int> v;
  std::generate_n(std::back_inserter(v), 10, [&]{return dis(gen);});

  f(v);

  for(auto&& e : v) std::cout << e << ' ';
  std::cout << '\n';
}
