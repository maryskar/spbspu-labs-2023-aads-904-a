#include <iostream>
#include <fstream>
#include <cstring>
#include <create-command-dictionary.hpp>
#include "read-map-of-int-string.hpp"
#include "create-args-map.hpp"
#include "key-summator.hpp"

int main(int argc, char ** argv)
{
  if (argc != 3)
  {
    std::cerr << "Incorrect amount of CML args\n";
    return 1;
  }

  std::ifstream input(argv[2]);
  if (!input.is_open())
  {
    std::cerr << "The file doesn't opened\n";
    return 1;
  }
  chemodurov::Map< int, std::string > data = chemodurov::readMapOfIntString(input);
  auto args = chemodurov::createArgsMap();
  if (data.empty())
  {
    chemodurov::outEmpty(std::cout);
  }
  else
  {
    try
    {
      chemodurov::KeySummator summator{};
      summator = data.traverse_lnr(summator);
      std::cout << summator.getSum() << ' ';
      chemodurov::Printer pr(std::cout);
      (data.*args.at(argv[1]))(pr);
    }
    catch (const std::out_of_range & e)
    {
      std::cerr << "Unexpected argument\n";
      return 1;
    }
    catch (const std::runtime_error & e)
    {
      std::cout << "Underflow or overflow in key sum\n";
      return 1;
    }
  }
  std::cout << '\n';
  return 0;
}
