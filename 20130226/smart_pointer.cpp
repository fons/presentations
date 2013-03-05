#include "proto.hpp"

class WInt {
public:
  explicit WInt(int v) : v(v){}
  WInt (const WInt& o) :v(o.v){}
  void operator=(const WInt&) = delete;
  int operator()() const {return v;};
private :
  int v;
};

//std::ostream& operator<<(std::ostream& strm, const WInt& w) {
//  return strm << w();
//}

int smart_1()
{
  std::shared_ptr<WInt> v1(new WInt(2));
  //  std::shared_pointer<WInt> v2(new WInt(2));
  std::shared_ptr<WInt> v2 = v1;
  if (v2 == v1) {
    std::cout << "they are equal !" << std::endl;
  }
  else {
    std::cout << "they are NOT equal !" << std::endl;
  }

}

int smart_2()
{
  std::shared_ptr<WInt> v1(new WInt(2));
  std::shared_ptr<WInt> v2(new WInt(2));

  if (v2 == v1) {
    std::cout << "they are equal !" << std::endl;
  }
  else {
    std::cout << "they are NOT equal !" << std::endl;
  }

}

bool operator==(const WInt& l, const WInt& r) {
  return l() == r();
}

int smart_3()
{
  std::shared_ptr<WInt> v1(new WInt(2));
  std::shared_ptr<WInt> v2(new WInt(2));

  
  if (*v2 == *v1) {
    std::cout << "they are equal !" << std::endl;
  }
  else {
    std::cout << "they are NOT equal !" << std::endl;
  }
  
}

int smart_4()
{
  auto mpure = [] (WInt v) {
    return std::shared_ptr<WInt> (new WInt (v));
  };

  auto v1 = mpure (WInt(5));
  auto v2 = mpure (WInt(5));

  if (*v2 == *v1) {
    std::cout << "they are equal !" << std::endl;
  }
  else {
    std::cout << "they are NOT equal !" << std::endl;
  }


}

template <typename A, typename F> F mpure(A t);
///keep in mind that this shouls work in the right context

template<typename A>
std::shared_ptr<A> mpure (A t) {
  return std::make_shared<A>(t);
}

template<>
int mpure (int t) {
  return t;
}

//template <typename A, typename B, typename F> F<B> mapply(F<std::function<B (A)>> f, F<A> v);

template <typename A, typename B> std::shared_ptr<B> mapply(std::shared_ptr<std::function<B (A)>> f, std::shared_ptr<A> v) {
  return mpure( (*f)(*v));
}


int smart_5()
{
  std::function<int (WInt)> f = [] (const WInt v) { return v();};
  //  std::shared_ptr<std::function<int (WInt)>> fp = std::make_shared<std::function<int (WInt)>>(f);
  std::shared_ptr<std::function<int (WInt)>> fp = std::make_shared<std::function<int (WInt)>>([] (const WInt v) { return v();});

  auto j = mpure(WInt(5));
  auto k = mpure(5);
  auto p = mpure(f);
  auto r = mapply(p, j);
  std::cout << *r << std::endl;
}

int smart_6()
{
  std::shared_ptr<void> p(nullptr);
  if (! p) {
    std::cout << "null pointer..." << std::endl;
  }
}
