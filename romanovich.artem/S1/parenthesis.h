#ifndef PARENTHESIS_H
#define PARENTHESIS_H
namespace romanovich
{
  enum class parenthesis_t: char
  {
    left = '(',
    right = ')',
  };
  char as_char(parenthesis_t parenthesis);
}
#endif
