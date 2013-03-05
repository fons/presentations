#ifndef __map__
#define __map__

template<typename T, typename U>
std::forward_list<U> map_helper_recur (std::function<U (T)>& op, std::forward_list<T>& L, std::forward_list<U>& acc)
{
  if (L.begin() == L.end()) {
    acc.reverse();
    return acc;
  }
  acc.push_front(op(L.front()));
  L.pop_front();
  return map_helper(op, L, acc);
}

template<typename T, typename U>
std::forward_list<U> map_helper (std::function<U (T)>& op, std::forward_list<T>& L, std::forward_list<U>& acc)
{
  while (! L.empty()) {
    acc.push_front(op(L.front()));
    L.pop_front();
  }
  acc.reverse();
  return acc;
}

//make this a forward list
template<typename T, typename U>
std::forward_list<U> map_fp (std::function<U (T)>& op, std::forward_list<T>& L)
{
  std::forward_list<U> acc;
  return map_helper(op, L, acc);
}

template<typename T, typename U>
std::forward_list<U> map_alt_recur (std::function<U (T)>& op, std::forward_list<T>& L)
{
  std::forward_list<U> acc;
  std::function  <std::forward_list<U> (std::forward_list<U>&) > helper = [&] (std::forward_list<U>& acc) -> std::forward_list<U>  {
    if (L.empty()) {
      acc.reverse();
      return acc;
    }
    acc.push_front(op(L.front()));
    L.pop_front();
    return helper(acc);
  };
  return helper(acc);
}

template<typename A, typename B>
std::forward_list<B> map (const std::function<B (A)>& op, const std::forward_list<A>& L)
{
  std::forward_list<B> acc;
  for (auto &v : L) {
    acc.push_front(op(v));
  }
  acc.reverse();
  return acc;
}

#endif
