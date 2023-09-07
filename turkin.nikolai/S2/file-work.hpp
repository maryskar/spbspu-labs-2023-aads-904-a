#ifndef FILE_HPP
#define FILE_HPP

#include <fstream>
#include <string>
#include <functional>
#include <cstddef>
#include <dictionary.hpp>

namespace turkin
{
  using dict_t = Dictionary< std::size_t, std::string, std::less< std::size_t > >;
  using dict_a = Dictionary< std::string, dict_t, std::less< std::string > >;
  dict_a genDicts(std::istream & input);
}

#endif
