#include "inputInfixQueue.h"
#include <cstring>
#include <iostream>
#include <cctype>
#include <stdexcept>
#include <string>
#include "valueType.h"
#include "queue.h"

std::istream& potapova::inputInfixQueue(potapova::Queue< potapova::ArithmExpMember >& dest, std::istream& in = std::cin)
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
      in.setstate(std::ios_base::failbit);
    }
    dest.push(member);
  }
  return in;
}

bool potapova::isOperation(char& sym)
{
  return (sym == '+' || sym == '-' || sym == '*' || sym == '/' || sym == '%' || sym == '(' || sym == ')');
}
