#ifndef SYMBOLS_H
#define SYMBOLS_H
#include <string>
namespace fesenko
{
  bool isOpenedBracket(std::string s);
  bool isClosedBracket(std::string s);
  bool isOperation(std::string s);
  bool isNumber(std::string s);
  size_t priority(std::string s);
  bool isBiggerPriority(std::string a, std::string b);
}
#endif
