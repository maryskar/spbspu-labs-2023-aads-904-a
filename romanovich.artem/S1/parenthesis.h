#ifndef PARENTHESIS_H
#define PARENTHESIS_H
enum class parenthesis_t: char
{
  left = '(',
  right = ')',
};
char as_char(parenthesis_t parenthesis);
#endif
