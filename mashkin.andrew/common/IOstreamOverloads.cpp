#include "IOstreamOverloads.h"
#include <iostream>
#include <iterator>
#include <string>
#include "AVL/AVL.h"
#include "dictionary.h"

namespace mashkin
{
  template< class T >
  std::istream& insertPairInDict(std::istream& inp, T& dict)
  {
    int key = 0;
    std::string value;
    inp >> key;
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
}
