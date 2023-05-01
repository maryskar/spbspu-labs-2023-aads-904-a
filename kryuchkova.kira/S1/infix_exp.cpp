#include "infix_exp.h"
#include <string>
#include <iostream>

namespace kryuchkova
{
  Queue< ExpressionMember > InfixExp(std::string &str)
  {
    Queue< ExpressionMember > inf;
    size_t j = 0;
    for (size_t i = 0; i < str.size(); i++)
    {
      if (str[i] != ' ')
      {
        if (str[i] == '(')
        {
          ExpressionMember data(parenthesis_t::OPEN);
          inf.push(data);
        }
        else if (str[i] == ')')
        {
          ExpressionMember data(parenthesis_t::CLOSE);
          inf.push(data);
        }
        else if (str[i] == '-')
        {
          ExpressionMember data(operation_t::SUBTRACTION);
          inf.push(data);
        }
        else if (str[i] == '+')
        {
          ExpressionMember data(operation_t::ADDITION);
          inf.push(data);
        }
        else if (str[i] == '*')
        {
          ExpressionMember data(operation_t::MULTIPLICATION);
          inf.push(data);
        }
        else if (str[i] == '/')
        {
          ExpressionMember data(operation_t::DIVISION);
          inf.push(data);
        }
        else if (str[i] == '%')
        {
          ExpressionMember data(operation_t::EUCLIDEAN_DIVISION);
          inf.push(data);
        }
        else
        {
          j = i;
          while (str[i + 1] != ' ')
          {
            i++;
          }
          long temp = std::stoll(str.substr(j, i + 1), std::addressof(j));
          ExpressionMember data(temp);
          inf.push(data);
        }
      }
    }
    return inf;
  }
}