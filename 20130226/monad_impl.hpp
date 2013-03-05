#ifndef H__MONAD_IMPL__H
#define H__MONAD_IMPL__H
template<> struct monad<proxy_list> : public applicative_functor<proxy_list> {
  
  template<typename A, typename B>
  static std::function < proxy_list<B> (std::function< proxy_list<B> (A) > ) > bind(proxy_list<A> xs) {
    return [=](std::function<proxy_list<B> (A)> f) {
      std::forward_list<B> R;
      std::forward_list<A> M = xs.L;
      std::forward_list<proxy_list<B>> res = map(f, M);
      for (auto& list : res) {
	std::forward_list<B>& l = list.L;
      	R.splice_after(R.before_begin(), list.L);//concatenate 
      }
      return R;
    };
  }

};

#endif
