#include <iostream>
#include <string>
#include "queue.h"
#include "parser.h"
#include "stack.h"
#include "part.h"
#include "functions.h"
int main()
{
  namespace dsk = dimkashelk;
  std::string element = "";
  while (std::cin)
  {
    std::getline(std::cin, element);
    try
    {
      dsk::Parser parser(element);
      dsk::Queue< dsk::part > data;
      while (parser.hasNext())
      {
        data.push(dsk::makePart(parser()));
      }
      dsk::Queue< dsk::part > queue;
      dsk::Stack< dsk::part > stack;
      while (!data.empty())
      {
        dsk::part p = data.drop();
        if (!p.isDigit_)
        {
          if (p.operator_ == ')')
          {
            if (stack.empty())
            {
              std::cerr << "Check";
              return 1;
            }
            dsk::part p1 = stack.drop();
            while (p1.operator_ != '(')
            {
              queue.push(p1);
              if (stack.empty())
              {
                std::cerr << "Check";
                return 1;
              }
              p1 = stack.drop();
            }
          }
          if (stack.empty())
          {
            stack.push(p);
          }
          else
          {
            dsk::part p1 = stack.drop();
            stack.push(p1);
            if (dsk::isPriorityOperation(p1.operator_, p.operator_))
            {
              stack.push(p);
            }
            else
            {
              p1 = stack.drop();
              while (!dsk::isPriorityOperation(p1.operator_, p.operator_))
              {
                queue.push(p1);
                if (stack.empty())
                {
                  break;
                }
                p1 = stack.drop();
              }
              stack.push(p);
            }
          }
        }
        else
        {
          queue.push(p);
        }
      }
      while (!stack.empty())
      {
        queue.push(stack.drop());
      }
      while (!queue.empty())
      {
        dsk::part p = queue.drop();
        if (p.isDigit_)
        {
          std::cout << p.operand_ << " ";
        }
        else
        {
          std::cout << p.operator_ << " ";
        }
      }
    }
    catch (...)
    {}
  }
  return 0;
}
