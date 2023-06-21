#ifndef FILE_HPP
#define FILE_HPP

#include <fstream>
#include <string>
#include <functional>
#include <cstddef>
#include "dictionary.hpp"

namespace turkin
{
  using dict = Dictionary< std::size_t, std::string, std::less< std::size_t > >;
  using dictArray = Dictionary< std::string, dict, std::less< std::string > >;
  dictArray genDicts(const std::ifstream & input);
}

#endif
