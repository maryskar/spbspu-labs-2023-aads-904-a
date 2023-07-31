#include <iostream>
#include <cstring>
#include <sort-and-print-random-value.hpp>
#include <map.hpp>

int main(int argc, char ** argv)
{
  if (argc != 4)
  {
    std::cerr << "Incorrect amount of CML args\n";
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
  if (!num_of_elem)
  {
    std::cerr << "Empty sequence\n";
    return 1;
  }
  using args_func_t = void(*)(std::ostream &, size_t);
  chemodurov::Map< std::string, args_func_t > args_map
  {
    {"ascending ints", chemodurov::sortAscendingInts},
    {"ascending floats", chemodurov::sortAscendingFloats},
    {"descending ints", chemodurov::sortDescendingInts},
    {"descending floats", chemodurov::sortDescendingFloats}
  };
  args_map.at(std::string(argv[1]) + ' ' + std::string(argv[2]))(std::cout, num_of_elem);
  return 0;
}
