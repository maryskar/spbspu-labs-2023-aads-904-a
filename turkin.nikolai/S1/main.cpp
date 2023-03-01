#include <iostream>
#include <string>
#include <fstream>
#include <queue.h>
#include <stack.h>
#include "data-type.h"

bool prt(char data)
{
  return !(data == '+' || data == '-');
}

int main(int argc, char * argv[])
{
  Queue< calc_t > input;
  Stack< calc_t > buffer;
  Queue< calc_t > output;
  std::string dirt, temp;
  calc_t data;
  if (argc == 2)
  {
    std::fstream file(argv[1]);
    if (!file.is_open())
    {
      std::cerr << "cannot open file\n";
      return 1;
    }
    std::getline(file, dirt);
  }
  dirt += '\n';
  std::cout << dirt;
  for (auto symbol : dirt)
  {
    if (symbol == ' ' || symbol == '\n')
    {
      try
      {
        data = std::stoll(temp);
      }
      catch (...)
      {
        data = temp.c_str()[0];
      }
      input.push(data);
      temp = "";
    }
    else
    {
      temp += symbol;
    }
  }
/////////////////////////////////////////////////////////////
  while (!input.isEmpty())
  {
    data = input.drop();
    if (data.isgigit)
    {
      output.push(data);
    }
    else
    {
      if (data.calc.sign == ')')
      {
        while (!buffer.isEmpty())
        {
          calc_t opt = buffer.drop();
          if (opt.calc.sign == '(')
          {
            break;
          }
          output.push(opt);
        }
      }
      else if (!buffer.isEmpty() && data.calc.sign != '(')
      {
        calc_t opt = buffer.drop();
        buffer.push(opt);
        if (prt(data.calc.sign) < prt(opt.calc.sign) || opt.calc.sign == '(')
        {
          buffer.push(data);
        }
        else
        {
          opt = buffer.drop();
          while (prt(data.calc.sign) >= prt(opt.calc.sign))
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
      else
      {
        buffer.push(data);
      }
    }
  }
  while (!buffer.isEmpty())
  {
    output.push(buffer.drop());
  }
//////////////////////////////////////////////////////////////
  while (!output.isEmpty())
  {
    calc_t opt = output.drop();
    if (opt.isgigit)
    {
      buffer.push(opt);
    }
    else
    {
      calc_t a = buffer.drop();
      calc_t b = buffer.drop();
      calc_t c;
      if (opt.calc.sign == '+')
      {
        c = b.calc.num + a.calc.num;
      }
      if (opt.calc.sign == '-')
      {
        c = b.calc.num - a.calc.num;
      }
      if (opt.calc.sign == '*')
      {
        c = b.calc.num * a.calc.num;
      }
      if (opt.calc.sign == '/')
      {
        c = b.calc.num / a.calc.num;
      }
      if (opt.calc.sign == '%')
      {
        c = b.calc.num % a.calc.num;
      }
      buffer.push(c);
    }
  }
  std::cout << buffer.drop().calc.num << "\n";
  return 0;
}
