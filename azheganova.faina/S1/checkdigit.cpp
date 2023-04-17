#include "checkdigit.h"

bool isDigit(const std::string & string)
{
  try
  {
    std::stoll(string, nullptr, 10);
  }
  catch (const std::exception & e)
  {
    return false;
  }
  return true;
}
