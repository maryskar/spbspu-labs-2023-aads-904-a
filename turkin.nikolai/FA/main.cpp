#include <iostream>
#include <string>

#include "data-types.hpp"
#include "commands-exe.hpp"

#include <out-msg.hpp>

int main()
{
  turkin::Execute execute;

  turkin::phrase_dict_t phrase;
  turkin::encoding_dict_t encoding;

  while (std::cin)
  {
    try
    {
      execute(phrase, encoding, std::cin, std::cout) << "\n";
    }
    catch (...)
    {
      turkin::outInvalidCMD(std::cout);
    }
  }
  return 0;
}
