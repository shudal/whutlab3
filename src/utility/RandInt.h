//
// Created by perci on 2020/6/14.
//

#ifndef COOK_SRC_UTILITY_RANDINT_H_
#define COOK_SRC_UTILITY_RANDINT_H_
#include <random>
class RandInt {
 public:
  // [low, high]
  RandInt(int low, int high) :dist{low,high} { }
  int operator()() { return dist(re); } // draw an int
 private:
  std::default_random_engine re;
  std::uniform_int_distribution<> dist;
};
#endif//COOK_SRC_UTILITY_RANDINT_H_
