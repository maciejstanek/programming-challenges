#include <iostream>

using namespace std;

template<int n>
constexpr long factorial()
{
  return n*factorial<n-1>();
}

template<>
constexpr long factorial<1>()
{
  return 1;
}

int main() {
  cout << "factorial<1>()  == " << factorial<1>() << endl;
  cout << "factorial<2>()  == " << factorial<2>() << endl;
  cout << "factorial<3>()  == " << factorial<3>() << endl;
  cout << "factorial<4>()  == " << factorial<4>() << endl;
  cout << "factorial<5>()  == " << factorial<5>() << endl;
  cout << "factorial<6>()  == " << factorial<6>() << endl;
  cout << "factorial<7>()  == " << factorial<7>() << endl;
  cout << "factorial<8>()  == " << factorial<8>() << endl;
  cout << "factorial<9>()  == " << factorial<9>() << endl;
  cout << "factorial<10>() == " << factorial<10>() << endl;
  cout << "factorial<11>() == " << factorial<11>() << endl;
  cout << "factorial<12>() == " << factorial<12>() << endl;
  cout << "factorial<13>() == " << factorial<13>() << endl;
  cout << "factorial<14>() == " << factorial<14>() << endl;
  cout << "factorial<15>() == " << factorial<15>() << endl;
  cout << "factorial<16>() == " << factorial<16>() << endl;
  cout << "factorial<17>() == " << factorial<17>() << endl;
  cout << "factorial<18>() == " << factorial<18>() << endl;
  cout << "factorial<19>() == " << factorial<19>() << endl;
  cout << "factorial<20>() == " << factorial<20>() << endl;
}
