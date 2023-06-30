#include "inputInfixQueue.h"
#include <cstring>
#include <cctype>
#include <string>

bool isOperation(const char& sym)
{
  return (sym == '+' || sym == '-' || sym == '*' || sym == '/' || sym == '%' || sym == '(' || sym == ')');
}

std::istream& potapova::inputInfixQueue(expr_queue& dest, std::istream& in)
{
  std::string expr_as_str;
  std::getline(in, expr_as_str);
  const char* cur_sym_ptr(expr_as_str.c_str());
  while (*cur_sym_ptr != '/0')
  {
    ArithmExpMember member;
    if (isdigit(*cur_sym_ptr))
    {
      member.type = ArithmExpMember::Type::Num;
      char* end_conv_ptr = nullptr;
      member.num = std::strtoll(cur_sym_ptr, &end_conv_ptr, 10);
      if (errno == ERANGE)
      {
        in.setstate(std::ios_base::failbit);
        break;
      }
      cur_sym_ptr = end_conv_ptr;
    }
    else if (isOperation(*cur_sym_ptr))
    {
      member.type = ArithmExpMember::Type::Operation;
      member.operation = *cur_sym_ptr++;
    }
    else
    {
      in.setstate(std::ios_base::failbit);
      break;
    }
    dest.push(member);
    if (isspace(*cur_sym_ptr))
    {
      ++cur_sym_ptr;
    }
  }
  return in;
}
