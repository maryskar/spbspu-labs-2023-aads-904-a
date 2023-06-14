#include "getInfixQueue.h"
#include <cstring>
#include <iostream>
#include <cctype>
#include <stdexcept>
#include <string>
#include "valueType.h"
#include "queue.h"

bool getInfixQueue(potapova::Queue< potapova::ArithmExpMember >& dest, std::istream& in = std::cin)
{
  std::string string_member;
  while (in >> string_member)
  {
    potapova::ArithmExpMember member;
    if (isdigit(string_member.front()))
    {
      member.type = potapova::ArithmExpMember::Type::Num;
      member.num = std::stoll(string_member);
    }
    else if (isOperation(string_member.front()))
    {
      member.type = potapova::ArithmExpMember::Type::Operation;
      member.operation = std::stoll(string_member);
    }
    else
    {
      throw std::logic_error("The parameters of the expression are incorrect");
    }
    dest.push(member);
  }
}

bool isOperation(char& sym)
{
  return (sym == '+' || sym == '-' || sym == '*' || sym == '/' || sym == '%' || sym == '(' || sym == ')');
}
