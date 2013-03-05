#ifndef H__FUNCTOR__H
#define H__FUNCTOR__H

template <template<typename T1> class F>
struct functor {
  template<typename A, typename B>
  static std::function < F<B> (F<A>)> fmap(std::function <B (A)> f);;
};

template <template<typename T1> class F> 
struct applicative_functor : public functor <F>
{

  template <typename A> 
  static F<A> pure(A val);

  template<typename A, typename B>
  static std::function < F<B> (F<A>)> apply(F <std::function<B(A)>> f );
};


#endif
