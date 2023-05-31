#include <iostream>
#include <cstring>
#include "sort-and-print-random-value.hpp"

int main(int argc, char ** argv)
{
  if (argc != 4)
  {
    std::cerr << "Incorrect amount of CML args\n";
    return 1;
  }
  if (std::strcmp(argv[1], "ascending") != 0 && std::strcmp(argv[1], "descending") != 0)
  {
    std::cerr << "Incorrect first argument\n";
    return 1;
  }
  size_t num_of_elem = 0;
  try
  {
    num_of_elem = std::strtoull(argv[3], nullptr, 10);
  }
  catch (...)
  {
    std::cerr << "Incorrect third argument\n";
    return 1;
  }
  using gen_t = std::default_random_engine;
  gen_t gen;
  if (!std::strcmp(argv[2], "ints"))
  {
    using distr_t = std::uniform_int_distribution< >;
    distr_t distr;
    if (!std::strcmp(argv[1], "ascending"))
    {
      using comp = std::less< >;
      chemodurov::sortAndPrintRandomValue< int, comp, distr_t, gen_t >(comp{}, distr, gen, std::cout, num_of_elem);
    }
    else
    {
      using comp = std::greater< >;
      chemodurov::sortAndPrintRandomValue< int, comp, distr_t, gen_t >(comp{}, distr, gen, std::cout, num_of_elem);
    }
  }
  else if (!std::strcmp(argv[2], "floats"))
  {
    using distr_t = std::uniform_real_distribution< >;
    distr_t distr;
    if (!std::strcmp(argv[1], "ascending"))
    {
      using comp = std::less< >;
      chemodurov::sortAndPrintRandomValue< double, comp, distr_t, gen_t >(comp{}, distr, gen, std::cout, num_of_elem);
    }
    else
    {
      using comp = std::greater< >;
      chemodurov::sortAndPrintRandomValue< double, comp, distr_t, gen_t >(comp{}, distr, gen, std::cout, num_of_elem);
    }
  }
  else
  {
    std::cerr << "Incorrect second argument\n";
    return 1;
  }
  return 0;
}
