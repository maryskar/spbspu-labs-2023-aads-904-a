#include <iostream>
#include <list>
#include <deque>
#include <algorithm>
#include <random>
#include <cstring>
#include <map.hpp>
#include <forward-list.hpp>
#include "shell-sort.hpp"
#include "timsort.hpp"

int main(int argc, char ** argv)
{
  if (argc != 4)
  {
    std::cerr << "Incorrect amount of CML args\n";
    return 1;
  }
  std::default_random_engine generator;
  if (!std::strcmp(argv[2], "ints"))
  {
    std::uniform_int_distribution< > distrib;

  }
  return 0;
}
