#include "proto.hpp"

int tuples_1()
{
  // city, state, zipcode
  auto t = std::make_tuple("Philadelphia", "PA", 12989);
  auto u = std::make_tuple("Philadelphia", "PA", 12989);
  if (t == u) {
    std::cout << "equal..." << std::endl;
  }

}

int tuples_2()
{
  // city, state, zipcode
  auto t = std::make_tuple("Philadelphia", "PA", std::make_tuple(1,2,"alfa"));
  std::cout << "city : " << std::get<0>(t) << std::endl;

  std::string city;
  std::string state;
  int val1;
  int val2;
  std::string g;

  std::make_tuple(std::ref(city),
		  std::ref(state),
		  std::make_tuple(std::ref(val1),
		  		  std::ref(val2),
		  		  std::ref(g))) = t;


  std::cout << "city : " << city << " : state : " << state << " g : " << g << std::endl;
  return 0;
}


