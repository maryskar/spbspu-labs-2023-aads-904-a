#include "exp-work.h"
#include <queue.h>
#include <stack.h>
#include "data-type.h"

bool getPriorityLevel(char data)
{
  return !(data == '+' || data == '-');
}

bool isOverflow(long long a, long long b)
{
    if (a == 0 || b == 0)
        return false;

    long long result = a * b;
    if (a == result / b)
        return false;
    else
        return true;
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
      if (data == ')')
      {
        while (!buffer.isEmpty())
        {
          calc_t opt = buffer.drop();
          if (opt == '(')
          {
            break;
          }
          output.push(opt);
        }
      }
      else if (!buffer.isEmpty() && data != '(')
      {
        calc_t opt = buffer.drop();
        buffer.push(opt);
        if (getPriorityLevel(data) < getPriorityLevel(opt) || opt == '(')
        {
          buffer.push(data);
        }
        else
        {
          opt = buffer.drop();
          while (getPriorityLevel(data) >= getPriorityLevel(opt))
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

void post2Result(Queue< calc_t > & output, long long & result)
{
  Stack< long long > buffer;
  while (!output.isEmpty())
  {
    calc_t opt = output.drop();
    if (opt.isgigit)
    {
      buffer.push(opt);
    }
    else
    {
      long long b = buffer.drop();
      long long  a = buffer.drop();
      long long c = 0;
      if (opt == '+')
      {
        if (a > 0 && b > 0 && (a + b < 0))
        {
          throw std::overflow_error("sum error");
        }
        c = a + b;
      }
      if (opt == '-')
      {
        if (a < 0 && b < 0 && (a + b > 0))
        {
          throw std::overflow_error("sum error");
        }
        c = a - b;
      }
      if (opt == '*')
      {
        if (isOverflow(a, b))
        {
          throw std::overflow_error("multiply error");
        }
        c = a * b;
      }
      if (opt == '/')
      {
        if (!b)
        {
          throw std::runtime_error("zero division");
        }
        c = a / b;
      }
      if (opt == '%')
      {
        if (!b)
        {
          throw std::runtime_error("zero division");
        }
        c = (a > 0) ? a % b : b - (-a) % b;
      }
      buffer.push(c);
    }
  }
  result = buffer.drop();
}
