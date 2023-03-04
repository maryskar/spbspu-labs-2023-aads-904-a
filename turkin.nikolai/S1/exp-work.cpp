#include "exp-work.h"
#include <queue.h>
#include <stack.h>
#include "data-type.h"

bool prt(char data)
{
  return !(data == '+' || data == '-');
}

void str2Inf(std::string & dirt, Queue< calc_t > & input)
{
  calc_t data;
  std::string temp;
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
}

void inf2Post(Queue< calc_t > & input, Queue< calc_t > & output)
{
  Stack< calc_t > buffer;
  while (!input.isEmpty())
  {
    calc_t data = input.drop();
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
}

void post2Result(Queue< calc_t> & output, long long & result)
{
  Stack< calc_t > buffer;
  while (!output.isEmpty())
  {
    calc_t opt = output.drop();
    if (opt.isgigit)
    {
      buffer.push(opt);
    }
    else
    {
      calc_t b = buffer.drop();
      calc_t a = buffer.drop();
      calc_t c;
      if (opt.calc.sign == '+')
      {
        if (a.calc.num > 0 && b.calc.num > 0 && (a.calc.num + b.calc.num < 0))
        {
          throw std::overflow_error("sum error");
        }
        c = a.calc.num + b.calc.num;
      }
      if (opt.calc.sign == '-')
      {
        if (a.calc.num < 0 && b.calc.num < 0 && (a.calc.num + b.calc.num > 0))
        {
          throw std::overflow_error("sum error");
        }
        c = a.calc.num - b.calc.num;
      }
      if (opt.calc.sign == '*')
      {
        if (a.calc.num != 0 && (a.calc.num * b.calc.num) / a.calc.num != b.calc.num)
        {
          c = a.calc.num * b.calc.num;
        }
      }
      if (opt.calc.sign == '/')
      {
        c = a.calc.num / b.calc.num;
      }
      if (opt.calc.sign == '%')
      {
        c = a.calc.num % b.calc.num;
      }
      buffer.push(c);
    }
  }
  result = buffer.drop();
}
