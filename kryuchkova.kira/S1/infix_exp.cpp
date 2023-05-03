#include "infix_exp.h"
#include <string>
#include <iostream>

namespace kryuchkova
{
  Queue< ExpressionMember > InfixExp(std::string &str)
  {
    Queue< ExpressionMember > inf;
    size_t j = 0;
    size_t i = 0;
    while (i < str.size())
    {
      if (str[i] == '(')
      {
        ExpressionMember data(parenthesis_t::OPEN);
        inf.push(data);
        i += 2;
      }
      else if (str[i] == ')')
      {
        ExpressionMember data(parenthesis_t::CLOSE);
        inf.push(data);
        i += 2;
      }
      else if (str[i] == '-')
      {
        ExpressionMember data(operation_t::SUBTRACTION);
        inf.push(data);
        i += 2;
      }
      else if (str[i] == '+')
      {
        ExpressionMember data(operation_t::ADDITION);
        inf.push(data);
        i += 2;
      }
      else if (str[i] == '*')
      {
        ExpressionMember data(operation_t::MULTIPLICATION);
        inf.push(data);
        i += 2;
      }
      else if (str[i] == '/')
      {
        ExpressionMember data(operation_t::DIVISION);
        inf.push(data);
        i += 2;
      }
      else if (str[i] == '%')
      {
        ExpressionMember data(operation_t::EUCLIDEAN_DIVISION);
        inf.push(data);
        i += 2;
      }
      else if (str[i] == ' ')
      {
        ++i;
      }
      else
      {
        // j = i;
        // while (str[i] != ' ')
        // {
        //   i++;
        // }
        long temp = std::stoll(str.substr(i), std::addressof(j));
        j += i;
        i = j;
        ExpressionMember data(temp);
        inf.push(data);
      }
    }
    return inf;
  }
}
