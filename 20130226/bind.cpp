#include "proto.hpp"

using namespace std;
using namespace std::placeholders;

int bind_1()
{

  auto l = std::bind(plus<int>(), _1, 10);
  auto r = l(902);
  cout << l(902) << endl;
  return 0;
}

int bind_2()
{

  auto l = std::bind([=](int x, int y){return 5 * x + y; }, _1, 10);
  auto r = l(902);
  cout << l(902) << endl;
  return 0;
}

// Bind is not curry...
int bind_3()
{

  auto l = std::bind([=](int x, int y){return 5 * x + y; }, _2, _1);
  auto r = l(10, 8);
  cout << r << endl;
  return 0;
}

int bind_4()
{
  auto l1     = [](int x, int y) { return x*y;};
  auto repeat = [](int n, int x) { int y = 1;
				   while (n-- > 0) y *= x;
				   return y;};

  auto rpl    = std::bind (repeat,
			   std::placeholders::_1,
			   std::bind(l1,
				     std::placeholders::_2,
				     std::placeholders::_3));

  std::cout << " l1 (1,2) : " << l1(1,2) << std::endl; 
  std::cout << " repeat (2,2) : " << repeat(2,2) << std::endl; 
  auto val = rpl(4, 1, 2); //( 1 * 2) ^ 4
  std::cout << " result : " << val << std::endl;

}
