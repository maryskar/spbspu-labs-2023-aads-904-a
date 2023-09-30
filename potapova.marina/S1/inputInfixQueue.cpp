#include "inputInfixQueue.h"
#include "arithmExpressionMember.h"
#include <cstring>
#include <cctype>
#include <string>

namespace
{
  bool isOperation(const char& sym)
  {
    return (sym == '+' || sym == '-' || sym == '*' || sym == '/' || sym == '%' || sym == '(' || sym == ')');
  }
}

std::istream& potapova::inputInfixQueue(expr_queue& dest, std::istream& in)
{
  std::string expr_as_str;
  std::getline(in, expr_as_str);
  const char* cur_sym_ptr(expr_as_str.c_str());
  while (*cur_sym_ptr != '\0')
  {
    ArithmExpMember member;
    if (std::isdigit(*cur_sym_ptr) || (*cur_sym_ptr == '-' && std::isdigit(*(cur_sym_ptr + 1))))
    {
      char* end_conv_ptr = nullptr;
      member = std::strtoll(cur_sym_ptr, &end_conv_ptr, 10);
      if (errno == ERANGE)
      {
        in.setstate(std::ios_base::failbit);
        break;
      }
      cur_sym_ptr = end_conv_ptr;
    }
    else if (isOperation(*cur_sym_ptr))
    {
      member = *cur_sym_ptr++;
    }
    else
    {
      in.setstate(std::ios_base::failbit);
      break;
    }
    dest.push(member);
    if (std::isspace(*cur_sym_ptr))
    {
      ++cur_sym_ptr;
    }
  }
  return in;
}
