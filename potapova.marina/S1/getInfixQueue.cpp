#include "getInfixQueue.h"
#include <cstring>
#include <iostream>
#include <cctype>
#include <stdexcept>
#include <string>
#include "valueType.h"
#include "queue.h"

potapova::Queue< potapova::ArithmExpMember > getInfixQueue()
{
  std::string string_member;
  if (!(std::cin >> string_member))
  {
    std::cerr << "Input error\n";
    return 1;
  }
  while (std::cin >> string_member)
  {
    potapova::ArithmExpMember member;
    if (isdigit(string_member.front()))
    {
      member.type = potapova::ArithmExpMember::Type::Num;
      member.num = std::stoll(string_member);
    }
    else if ()
    {
      member.type = potapova::ArithmExpMember::Type::Operation;
      member.operation = std::stoll(string_member);
    }
    else
    {
      throw std::logic_error("The parameters of the expression are incorrect");
    }
  }
}


