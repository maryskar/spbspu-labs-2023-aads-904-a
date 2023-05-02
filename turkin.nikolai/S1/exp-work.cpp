#include "exp-work.hpp"
#include <queue.hpp>
#include <stack.hpp>
#include "data-type.hpp"
#include "calc-verify.hpp"
#include "assimitation.hpp"

using pinf_t = turkin::datatype::calc_t< turkin::datatype::PINF >;
using pfix_t = turkin::datatype::calc_t< turkin::datatype::PFIX >;
using PINF = turkin::datatype::PINF;
using PFIX = turkin::datatype::PFIX;
namespace asml = turkin::assimilation;
namespace vrfy = turkin::verify;
namespace cnvt = turkin::convert;

bool getPriorityLevel(pfix_t data)
{
  return !(asml::same(data, PFIX::ADD) || asml::same(data, PFIX::SUB));
}

turkin::Queue< pinf_t > str2Inf(std::string & dirt)
{
  turkin::Queue< pinf_t > input;
  std::string temp;
  for (auto symbol : dirt)
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
        pinf_t data(sign, static_cast< PINF >(sign));
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

turkin::Queue< pfix_t > inf2Post(turkin::Queue< pinf_t > & input)
{
  turkin::Stack< pinf_t > buffer;
  turkin::Queue< pfix_t > output;
  while (!input.isEmpty())
  {
    pinf_t data(input.drop());
    if (asml::same(data, PINF::NUM))
    {
      output.push(cnvt::convertINF2FIX(data));
    }
    else
    {
      if (asml::same(data, PINF::RIGHT_BRACKET))
      {
        while (!buffer.isEmpty())
        {
          pinf_t opt = buffer.drop();
          if (asml::same(opt, PINF::LEFT_BRACKET))
          {
            break;
          }
          output.push(cnvt::convertINF2FIX(opt));
        }
      }
      else if (!buffer.isEmpty() && !asml::same(data, PINF::LEFT_BRACKET))
      {
        pinf_t opt(buffer.drop());
        buffer.push(opt);
        if (getPriorityLevel(cnvt::convertINF2FIX(data)) < getPriorityLevel(cnvt::convertINF2FIX(opt)) || asml::same(opt, PINF::LEFT_BRACKET))
        {
          buffer.push(data);
        }
        else
        {
          opt = buffer.drop();
          while (getPriorityLevel(cnvt::convertINF2FIX(data)) >= getPriorityLevel(cnvt::convertINF2FIX(opt)))
          {
            output.push(cnvt::convertINF2FIX(opt));
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
    output.push(cnvt::convertINF2FIX(buffer.drop()));
  }
  return output;
}

long long post2Result(turkin::Queue< pfix_t > & output)
{
  turkin::Stack< long long > buffer;
  while (!output.isEmpty())
  {
    pfix_t opt(output.drop());
    if (asml::same(opt, PFIX::NUM))
    {
      buffer.push(opt.calc.num);
    }
    else
    {
      long long b = buffer.drop();
      long long a = buffer.drop();
      long long c = 0;
      if (asml::same(opt, PFIX::ADD))
      {
        if (vrfy::isADDerror(a, b))
        {
          throw std::overflow_error("ADD error");
        }
        c = a + b;
      }
      if (asml::same(opt, PFIX::SUB))
      {
        if (turkin::verify::isSUBerror(a, b))
        {
          throw std::overflow_error("SUB error");
        }
        c = a - b;
      }
      if (asml::same(opt, PFIX::MUL))
      {
        if (turkin::verify::isMULerror(a, b))
        {
          throw std::overflow_error("MUL error");
        }
        c = a * b;
      }
      if (asml::same(opt, PFIX::DIV))
      {
        if (turkin::verify::isDIVerror(a, b))
        {
          throw std::runtime_error("zero division");
        }
        c = a / b;
      }
      if (asml::same(opt, PFIX::MOD))
      {
        if (turkin::verify::isMODerror(a, b))
        {
          throw std::runtime_error("zero division");
        }
        c = (a > 0) ? a % b : b + a % b;
      }
      buffer.push(c);
    }
  }
  return buffer.drop();
}
