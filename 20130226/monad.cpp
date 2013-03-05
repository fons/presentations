#include "proto.hpp"
#include "functor.hpp"
#include "functor_impl.hpp"
#include "monad.hpp"
#include "monad_impl.hpp"


// [a] -> (a ->[b]) ->[b]
template<typename A>
std::forward_list<A> bind_list (std::forward_list<A> L, std::function<std::forward_list<A> (A)> f)
{
  std::function<std::forward_list<A> (std::forward_list<A>, std::forward_list<A>)> concat = [] (std::forward_list<A> L, std::forward_list<A> R) { L.splice_after(L.before_begin(), R); return L;};
  auto op = std::bind(concat, std::placeholders::_1, std::bind(f, std::placeholders::_2));
  return std::accumulate(L.begin(), L.end(), std::forward_list<A>(), op);;
}


int m_1()
{
  typedef std::forward_list<int> list_t;
  list_t L = {1,-6,23,78,45,13};
  std::function<list_t (int)> l1 = [] (int y) {list_t K; K.push_front(2*y +1); return K;};  
  auto res1 = bind_list(L, l1);
  std::cout << "results : " << std::endl;
  for (auto& v: res1) {
    std::cout << v << std::endl;
  }
}



int m_2()
{
  std::forward_list<int> L = {1,3,45,78};
  auto op = [=](int x) {
    std::forward_list<int> R = {x , -x};
    return R;
  };
  proxy_list<int> r = monad<proxy_list>::bind<int,int>(L)(op);
  for (auto& v: r.L) {
     std::cout<< v << "," ;
  }
  std::cout << std::endl;
}

int m_3()
{
  std::forward_list<int> L = {1,2};
  int _x_;
  auto op = [&](int x) {
    _x_ = x;
    std::forward_list<char> R = {'a' , 'b'};
    return R;
  };

  auto op2 = [&] (char c) {
    std::forward_list<std::pair<char,int>> R;
    auto el = std::make_pair(c,_x_);
    R.push_front(el);
    return R;
  };
  
  auto R = monad<proxy_list>::bind<char, std::pair<char,int>>(monad<proxy_list>::bind<int,char>(L)(op))(op2);

  for (auto& v: R.L) {
    std::cout << "(" << v.first << "," << v.second << ")," ;
  }
  std::cout << std::endl;
  return 0;
}

int m_4()
{
  std::forward_list<int> L = {1,2};
  auto op = [=](int x) {
    std::forward_list<char> R = {'a' , 'b'};
    return R;
  };

  auto R = monad<proxy_list>::bind<int,char>(L)(op);
  for (auto& v: R.L) {
    std::cout << v << ",";
  }
  std::cout << std::endl;
  return 0;
}

template <typename B>
struct function_proxy {
  typedef int arg_t;
  function_proxy(const std::function<B(arg_t)> f) : func(f){}
  function_proxy(const function_proxy& fp):func(fp.func){}
  void operator=(const function_proxy& fp) = delete;
  B operator()(arg_t v) {
    return func(v);
  }
  std::function<B(arg_t)> func;
};

template <typename B>
struct function_proxy_alt {
  template <typename R>
  function_proxy_alt(const std::function<B(R)> f) {
    ptr = new inner<R>(f);
  }

  function_proxy_alt(const function_proxy_alt& fp):ptr(fp.ptr){}
  template<typename R>
  void operator=(const function_proxy_alt& fp) = delete;

  template<typename R>
  B operator()(R v) {
    inner<R>* wptr = static_cast<inner<R>>(ptr);
    return wptr->func(v);
  }
  template <typename R>
  struct inner {
    inner(const std::function<B(R)>& f) : func(f){}
    inner(const inner& obj) : func(obj.func){};
    std::function<B(R)> func;
  };
  //inner<void> W;
  void *ptr;
};



template <>
struct applicative_functor <function_proxy> 
{
  
  template <typename A> 
  static function_proxy<A> pure(A val) {
    return function_proxy<A>( [=] (typename function_proxy<A>::arg_t x) {
      return val;
      });
  }

  template<typename A, typename B>
  static std::function < function_proxy<B> (function_proxy<A>)> apply(function_proxy<std::function<B(A)>> f ) {
    return [] (int v) {
      return B();
    };
  }
};


int m_5()
{
  std::function<int (int)> op = [] (int v) { return 2*v;};
  function_proxy_alt<int> pop2 (op);
  function_proxy<int> pop (op);
  auto val = applicative_functor<function_proxy>::pure(56);
  std::cout << " pure (56) : "<< val(89) << std::endl;
}
