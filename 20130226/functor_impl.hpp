#ifndef H__FUNCTOR_IMPL_H
#define H__FUNCTOR_IMPL_H

#include "map.hpp"

template <>
struct functor<std::shared_ptr> {
  template<typename A, typename B>
  static std::function<std::shared_ptr<B> (std::shared_ptr<A>)>  fmap (std::function<B(A)> f) {
    return [=](std::shared_ptr<A> v) {
      if (v) {
	return std::make_shared<B>(f(*v)); 
      }
      return  std::shared_ptr<B>(nullptr);
    };
  }
};



template<>
struct applicative_functor <std::shared_ptr> : public functor<std::shared_ptr>
{

  template<typename A>
  static std::shared_ptr<A> pure(A val) {
    return std::make_shared<A>(val);
  }
  
  template<typename A, typename B>
  static std::function< std::shared_ptr<B> (std::shared_ptr<A> v)> apply(std::shared_ptr<std::function<B(A)>> f) {
      return [=](std::shared_ptr<A> v) {
	if (v && f) {
	  auto F = *f;
	  return pure (F(*v)); 
	}
	return  std::shared_ptr<B>(nullptr);
      };
    }
    
};

template <typename T> 
struct proxy_list {
  proxy_list(const std::forward_list<T>& L) : L(L) {}
  proxy_list(const proxy_list& obj) : L(obj.L) {}
  void operator=(const proxy_list& obj) = delete;
  std::forward_list<T> L; //cannot be reference because it may hold ref to stack; cannot be const
};

template<> struct 
functor<proxy_list> {
  template<typename A, typename B>
  static std::function < proxy_list<B> (proxy_list<A>)> fmap(std::function <B (A)> f) {
    return [=] (proxy_list<A> L) {
      return map<A,B>(f,L.L);
    };
  };
};

template<> struct 
applicative_functor<proxy_list> :public functor<proxy_list>{

  template<typename A>
  static proxy_list<A> pure(A v) {
    std::forward_list<A> L;
    L.push_front(v);
    return L;
  }
  
  template<typename A, typename B>
  static std::function< proxy_list<B> (proxy_list<A>)> apply(proxy_list<std::function<B(A)>> f) {
      return [=](proxy_list<A> v) {
	std::forward_list<B> acc;
	const std::forward_list<std::function<B(A)>>& F = f.L;
	const std::forward_list<A>& L = v.L;
	for (auto& func : F) {
	  for (auto& arg : L) {
	    acc.push_front(func(arg));
	  }
	 } 
	acc.reverse();
	return acc;
      };
    };

};

#endif
