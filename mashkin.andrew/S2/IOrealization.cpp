#include "IOrealization.h"
#include <iostream>
#include <iterator>
#include <string>
#include "dictionary.h"

namespace mashkin
{
  std::istream& operator>>(std::istream& inp, dictionary& dict)
  {
    std::istream::sentry sentry(inp);
    if (!sentry)
    {
      return inp;
    }
    int key;
    std::string value;
    inp >> key;
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
}
