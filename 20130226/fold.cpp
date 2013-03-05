#include "proto.hpp"

template <typename T, typename U>
U foldl(std::function< U (U, T)>& op, const U& val, const std::forward_list<T>& L)
{
  U acc(val);
  for (auto &v : L) {
    acc = op(acc, v);
  }
  return acc;
}


template <typename T, typename U>
U foldl(std::function< U (U, T)>& op, const std::forward_list<T>& L)
{
  U acc = U();
  for (auto &v : L) {
    acc = op(acc, v);
  }
  return acc;
}

template <typename T, typename U>
U foldr_dest(std::function< U (U, T)>& op, const U& val, std::forward_list<T>& L)
{
  if (L.empty()) return U(val);
  T h = L.front();
  L.pop_front();
  return op (foldr(op, val, L),  h);
}

template <typename T, typename U>
U foldr_dest(std::function< U (U, T)>& op, std::forward_list<T>& L)
{

  if (L.empty()) return U();
  T h = L.front();
  L.pop_front();
  return op (foldr(op, L),  h);
}

/*
template <typename T, typename U>
U foldr(std::function< U (U, T)>& op, const std::forward_list<T>& L)
{

  typedef typename std::forward_list<T>::iterator flit;

  std::function<U (const flit& it) > helper = [&] (const flit& it) {
    if (it == L.end()) return U();
    T& h = *flit;
    it++;
    return op (helper(it), h);
  }
  return helper(L.begin());
}
*/
  //  if (L.empty()) return U();
  //T h = L.front();
 // L.pop_front();
 // op (foldr(op, L),  h);

//}

int fold_1()
{
  std::forward_list<int> L = {1,-6,23,78,45,13};
  //std::function<int (int, int) > max = [] (int x, int y) { if (x > y) {return x;} else {return y;}};
  std::function<int (int, int) > max = [] (int x, int y) { return (x > y) ? x : y;};
  auto m = foldl(max, L);
  std::cout << m << std::endl;
  return 0;
}

int fold_2()
{
  std::forward_list<int> L = {1,-6,23,78,45,13};
  //std::function<int (int, int) > max = [] (int x, int y) { if (x > y) {return x;} else {return y;}};
  std::function<int (int, int) > max = [] (int x, int y) { return (x > y) ? x : y;};
  auto m = foldl(max, L);
  std::cout << m << std::endl;
  return 0;
}

