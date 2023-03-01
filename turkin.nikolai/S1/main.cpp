#include <iostream>
#include <string>
#include <queue.h>
#include <stack.h>
#include "data-type.h"

int main()
{
  Queue< calc_t > input;
  Stack< calc_t > buffer;
  Queue< calc_t > output;
  std::string dirt, temp;
  calc_t data, opt;
  std::getline(std::cin, dirt);
  dirt += '\n';
  for (auto symbol : dirt)
  {
    if (symbol == ' ' || symbol == '\n')
    {

      temp = "";
    }
    else
    {
      temp += symbol;
    }
  }
  while (!input.isEmpty())
  {
    data = input.drop();
    try
      {
        data = temp.c_str()[0];
        if (data.calc.sign == ')' && !buffer.isEmpty())
        {
          calc_t opt = buffer.drop();
          while (opt.calc.sign != '(' && !buffer.isEmpty())
          {
            output.push(opt);
            opt = buffer.drop();
          }
        }
        else if (buffer.isEmpty())
        {
          buffer.push(data);
        }
        else
        {
          opt = buffer.drop();
          buffer.push(opt);
          char one = opt.calc.sign;
          char two = data.calc.sign;
          while (two == '(' || ((one == '+' || one == '-') && (two == '*' || two == '/' || two == '%')))
          {
            output.push(opt);
            if (buffer.isEmpty())
            {
              break;
            }
            opt = buffer.drop();
          }
          buffer.push(data);
        }
      }
      catch (...)
      {
        data = std::stoll(temp);
        output.push(data);
      }
  }
  while (!buffer.isEmpty())
  {
    output.push(buffer.drop());
  }
  ///////////////////////////////////////////////
  ///////////////////////////////////////////////
  while (!output.isEmpty())
  {
    calc_t hh = output.drop();
    if (hh.isgigit)
    {
      std::cout << hh.calc.num << " ";
    }
    else
    {
      std::cout << hh.calc.sign << " ";
    }
  }
  return 0;
}