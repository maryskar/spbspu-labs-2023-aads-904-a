#include "IOrealization.h"
#include <iostream>
#include <iterator>
#include <string>
#include <limits>
#include <stdexcept>
#include "AVL.h"
#include "queue.h"
#include "stack.h"

namespace mashkin
{
  constexpr long maxInt = std::numeric_limits< int >::max();
  constexpr long minInt = std::numeric_limits< int >::min();

  std::istream& operator>>(std::istream& inp, dictionary& dict)
  {
    std::istream::sentry sentry(inp);
    if (!sentry)
    {
      return inp;
    }
    long long var;
    std::string value;
    inp >> var;
    if (var > maxInt)
    {
      throw std::overflow_error("Overflow of int");
    }
    else if (var < minInt)
    {
      throw std::underflow_error("Underflow of int");
    }
    int key = static_cast< int >(var);
    if (inp.peek() == '\n')
    {
      inp.setstate(std::ios::failbit);
      return inp;
    }
    inp >> value;
    if (!inp)
    {
      return inp;
    }
    if (inp.peek() == '\n')
    {
      inp.setstate(std::ios::eofbit);
    }
    dict.insert({key, value});
    return inp;
  }

  std::istream& operator>>(std::istream& inp, dictionaries& dicts)
  {
    std::istream::sentry sentry(inp);
    if (!sentry)
    {
      return inp;
    }
    std::string key;
    inp >> key;
    if (inp.peek() == '\n')
    {
      inp.setstate(std::ios::eofbit);
    }
    if (!inp)
    {
      return inp;
    }
    dictionary value;
    using inpIter = std::istream_iterator< dictionary >;
    auto i = inpIter(inp);
    while (!inp.eof() && i != inpIter())
    {
      ++i;
    }
    if (inp.eof())
    {
      inp.clear();
    }
    value.insert(i->begin(), i->end());
    dicts.insert({key, value});
    return inp;
  }

  iofmtguard::iofmtguard(std::basic_ios< char >& s):
    s_(s),
    fill_(s.fill()),
    precision_(s.precision()),
    fmt_(s.flags())
  {
  }

  iofmtguard::~iofmtguard()
  {
    s_.fill(fill_);
    s_.precision(precision_);
    s_.flags(fmt_);
  }

  std::ostream& operator<<(std::ostream& out, const dictionary& dicts)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    iofmtguard fmtguard(out);
    for (auto it = dicts.begin(); it != dicts.end(); it++)
    {
      out << " " << it->first << " " << it->second;
    }
    return out;
  }

  std::ostream& operator<<(std::ostream& out, const Queue< std::string >& que)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    iofmtguard fmtguard(out);
    Queue< std::string > res(que);
    while (res.isEmpty())
    {
      out << res.getHead();
      res.dequeue();
      if (res.isEmpty())
      {
        out << " ";
      }
    }
    return out;
  }

  std::ostream& operator<<(std::ostream& out, const Stack< std::string >& stack)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    iofmtguard fmtguard(out);
    Stack< std::string > res(stack);
    while (res.isEmpty())
    {
      out << res.getTop();
      res.pop();
      if (res.isEmpty())
      {
        out << " ";
      }
    }
    return out;
  }

  std::ostream& operator<<(std::ostream& out, const QueueForTraverse& queueForTraverse)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    iofmtguard fmtguard(out);
    out << queueForTraverse.summ_ << " " << queueForTraverse.res_;
    return out;
  }

  std::ostream& operator<<(std::ostream& out, const StackForTraverse& stackForTraverse)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    iofmtguard fmtguard(out);
    out << stackForTraverse.summ_ << " " << stackForTraverse.res_;
    return out;
  }
}
