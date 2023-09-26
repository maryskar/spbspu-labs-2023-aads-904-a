#include "IOstreamOverloads.h"
#include <iostream>
#include <iterator>
#include <string>
#include <limits>
#include "AVL/AVL.h"
#include "dictionary.h"

namespace mashkin
{
  constexpr long maxInt = std::numeric_limits< int >::max();
  constexpr long minInt = std::numeric_limits< int >::min();

  template< class T >
  std::istream& insertPairInDict(std::istream& inp, T& dict)
  {
    std::string value;
    long var;
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
    if (!inp)
    {
      return inp;
    }
    inp >> value;
    if (!inp)
    {
      return inp;
    }
    dict.insert({key, value});
    return inp;
  }

  template< class T >
  std::istream& insertDictInDictionaries(std::istream& inp, T& dicts)
  {
    std::string key;
    inp >> key;
    if (!inp)
    {
      return inp;
    }
    decltype(dicts.begin()->second) value;
    using inpIter = std::istream_iterator< decltype(value) >;
    auto i = inpIter(inp);
    while (!inp.eof() && i != inpIter())
    {
      ++i;
    }
    value.insert(i->begin(), i->end());
    dicts.insert({key, value});
    return inp;
  }

  template< class T >
  std::ostream& printDictionaries(std::ostream& out, const T& dicts)
  {
    for (auto it = dicts.begin(); it != dicts.end(); it++)
    {
      out << " " << it->first << " " << it->second;
    }
    return out;
  }

  std::istream& operator>>(std::istream& inp, AVL< int, std::string >& dict)
  {
    std::istream::sentry sentry(inp);
    if (!sentry)
    {
      return inp;
    }
    return insertPairInDict(inp, dict);
  }

  std::istream& operator>>(std::istream& inp, AVL< std::string, AVL< int, std::string > >& dicts)
  {
    std::istream::sentry sentry(inp);
    if (!sentry)
    {
      return inp;
    }
    return insertDictInDictionaries(inp, dicts);
  }

  std::ostream& operator<<(std::ostream& out, const AVL< int, std::string >& dicts)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    return printDictionaries(out, dicts);
  }

  std::istream& operator>>(std::istream& inp, Dictionary< int, std::string >& dict)
  {
    std::istream::sentry sentry(inp);
    if (!sentry)
    {
      return inp;
    }
    return insertPairInDict(inp, dict);
  }

  std::istream& operator>>(std::istream& inp, Dictionary< std::string, Dictionary< int, std::string > >& dicts)
  {
    std::istream::sentry sentry(inp);
    if (!sentry)
    {
      return inp;
    }
    return insertDictInDictionaries(inp, dicts);
  }

  std::ostream& operator<<(std::ostream& out, const Dictionary< int, std::string >& dicts)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    return printDictionaries(out, dicts);
  }

  std::ostream& operator<<(std::ostream& out, const Queue< std::string >& que)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
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
    out << stackForTraverse.summ_ << " " << stackForTraverse.res_;
    return out;
  }
}
