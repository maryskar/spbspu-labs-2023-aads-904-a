#include "exp-work.hpp"
#include <queue.hpp>
#include <stack.hpp>
#include "data-type.hpp"
#include "calc-verify.hpp"
#include "convert.hpp"

using pinf_t = turkin::calc_t< turkin::PINF >;
using pfix_t = turkin::calc_t< turkin::PFIX >;
using PINF = turkin::PINF;
using PFIX = turkin::PFIX;

namespace
{
  bool getPriorityLevel(const pinf_t & data)
  {
    return !(data.getType() == PINF::ADD || data.getType() == PINF::SUB);
  }
}

bool isLowerPriority(const pinf_t & lhs, const pinf_t & rhs)
{
  return getPriorityLevel(lhs) < getPriorityLevel(rhs);
}

turkin::Queue< pinf_t > turkin::str2Inf(std::string & dirt)
{
  Queue< pinf_t > input;
  std::string temp;
  for (auto symbol: dirt)
  {
    if (symbol == ' ' || symbol == '\n')
    {
      try
      {
        pinf_t data(std::stoll(temp), PINF::NUM);
        input.push(data);
      }
      catch (...)
      {
        char sign = temp.c_str()[0];
        PINF ins = PINF::ADD;
        if (sign == '+')
        {
          ins = PINF::ADD;
        }
        else if (sign == '-')
        {
          ins = PINF::SUB;
        }
        else if (sign == '*')
        {
          ins = PINF::MUL;
        }
        else if (sign == '/')
        {
          ins = PINF::DIV;
        }
        else if (sign == '%')
        {
          ins = PINF::MOD;
        }
        else if (sign == '(')
        {
          ins = PINF::LEFT_BRACKET;
        }
        else if (sign == ')')
        {
          ins = PINF::RIGHT_BRACKET;
        }
        pinf_t data(0ll, ins);
        input.push(data);
      }
      temp = "";
    }
    else
    {
      temp += symbol;
    }
  }
  return input;
}

turkin::Queue< pfix_t > turkin::inf2Post(Queue< pinf_t > & input)
{
  Stack< pinf_t > buffer;
  Queue< pfix_t > output;
  while (!input.isEmpty())
  {
    pinf_t data(input.get());
    input.pop();
    if (data.getType() == PINF::NUM)
    {
      output.push(convertINF2FIX(data));
    }
    else
    {
      if (data.getType() == PINF::RIGHT_BRACKET)
      {
        while (!buffer.isEmpty())
        {
          pinf_t opt = buffer.get();
          buffer.pop();
          if (opt.getType() == PINF::LEFT_BRACKET)
          {
            break;
          }
          output.push(convertINF2FIX(opt));
        }
      }
      else if (!buffer.isEmpty() && data.getType() != PINF::LEFT_BRACKET)
      {
        pinf_t opt(buffer.get());
        if (isLowerPriority(data, opt) || opt.getType() == PINF::LEFT_BRACKET)
        {
          buffer.push(data);
        }
        else
        {
          pinf_t opt(buffer.get());
          buffer.pop();
          while (!isLowerPriority(data, opt))
          {
            output.push(convertINF2FIX(opt));
            if (buffer.isEmpty())
            {
              break;
            }
            pinf_t opt(buffer.get());
            buffer.pop();
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
    output.push(convertINF2FIX(buffer.get()));
    buffer.pop();
  }
  return output;
}

long long turkin::post2Result(Queue< pfix_t > & output)
{
  Stack< long long > buffer;
  while (!output.isEmpty())
  {
    pfix_t opt(output.get());
    output.pop();
    if (opt.getType() == PFIX::NUM)
    {
      buffer.push(opt.getNum());
    }
    else
    {
      long long b = buffer.get();
      buffer.pop();
      long long a = buffer.get();
      buffer.pop();
      long long c = 0;
      if (opt.getType() == PFIX::ADD)
      {
        if (isADDerror(a, b))
        {
          throw std::overflow_error("ADD error");
        }
        c = a + b;
      }
      if (opt.getType() == PFIX::SUB)
      {
        if (isSUBerror(a, b))
        {
          throw std::overflow_error("SUB error");
        }
        c = a - b;
      }
      if (opt.getType() == PFIX::MUL)
      {
        if (isMULerror(a, b))
        {
          throw std::overflow_error("MUL error");
        }
        c = a * b;
      }
      if (opt.getType() == PFIX::DIV)
      {
        if (isDIVerror(a, b))
        {
          throw std::runtime_error("zero division");
        }
        c = a / b;
      }
      if (opt.getType() == PFIX::MOD)
      {
        if (isMODerror(a, b))
        {
          throw std::runtime_error("zero division");
        }
        c = (a > 0) ? a % b : b + a % b;
      }
      buffer.push(c);
    }
  }
  return buffer.get();
}
