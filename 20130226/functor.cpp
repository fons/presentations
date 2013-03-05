#include "proto.hpp"
#include "map.hpp"
#include "functor.hpp"
#include "functor_impl.hpp"

using namespace std;

struct W {

  explicit W(int v, const std::string& s) : v(v), s(s){}
  W(const W& o) : v(o.v), s(o.s){}
  void operator=(const W& o) = delete;

  int ssn() const { return v;}
  std::string name() const {return s;}
  std::ostream& pp(std::ostream& os) const {
    return os << "name : " << s << " ssn :" << v << " ";
  }
private :
  int v;
  std::string s;
};

std::ostream& operator<<(std::ostream& os, const W& w)
{
  return w.pp(os);
}

W operator+(const W& lhs, const W& rhs)
{
  std::string s(lhs.name());
  s.append(rhs.name());
  return W(lhs.ssn() + rhs.ssn(), s);
}

bool operator==(const W& lhs, const W& rhs)
{
  return (lhs.ssn() == rhs.ssn()) and (lhs.name() == rhs.name());
}

bool operator!=(const W& lhs, const W& rhs)
{
  return ! (lhs == rhs);
}

int w_1()
{
  W id(0,"");
  W val_1(1256, "hello");
  W val_2(-9088, "goodbye");
  W val_3(786, "haha");

  if ((id + val_1) == (val_1 + id)) {
    std::cout << "have indentity element" << std::endl;
  }
  
  if ((val_3 + (val_2 + val_1)) == ((val_3 + val_2) + val_1)) {
    std::cout << "have associativity" << std::endl;
  }
  
  return 0;
}


int functor_1()
{

  std::function<int (W)> show =[](W w) { w.pp(std::cerr) << std::endl; return w.ssn();};

  auto p = applicative_functor<std::shared_ptr>::pure(W(1090867, "hello_kitty"));
  auto s = applicative_functor<std::shared_ptr>::pure(show);
  std::cout << p << std::endl;
  applicative_functor<std::shared_ptr>::fmap(show)(p);
  applicative_functor<std::shared_ptr>::apply(s)(p);
  
}


int functor_2()
{
  std::forward_list<W> L = {W(10, "a"), W(20, "b"), W(3467, "mnhjk")};
  std::function<int (W)> show =[](W w) { w.pp(std::cerr) << std::endl; return w.ssn();};
  functor<proxy_list>::fmap(show)(L);
}

int functor_3()
{
  std::forward_list<int> K = {2, 5, 10};
  std::forward_list<int> L = {8, 10, 11};
  std::function<int(int)> show = [=](int v) { 
    std::cout << v << ",";
    return v;
  };
  std::function < std::function < int (int) > (int)> plus = [] (int x) {
    return [=] (int y) {
      return x + y;
    };
  };

  auto ls  = applicative_functor<proxy_list>::pure(show);
  auto lp  = applicative_functor<proxy_list>::pure(plus);
  auto kl  = applicative_functor<proxy_list>::apply(lp)(K);
  auto M   = applicative_functor<proxy_list>::apply(kl)(L);

  applicative_functor<proxy_list>::apply(ls)(K);
  std::cout << endl;
  applicative_functor<proxy_list>::apply(ls)(L);
  std::cout << endl;
  applicative_functor<proxy_list>::apply(ls)(M);
  std::cout << endl;
}

