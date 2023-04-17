#include "checkdigit.h"

bool isDigit(const std::string & string)
{
  try
  {
    std::stoll(string, nullptr, 10);
  }
  catch (...)
  {
    return false;
  }
  return true;
}
