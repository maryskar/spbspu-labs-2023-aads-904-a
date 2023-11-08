#ifndef STREAM_PROCESSING_S2_H
#define STREAM_PROCESSING_S2_H

#include <string>
#include <iosfwd>
#include <functional>
#include "ForwardList.h"
#include "CommandsS2.h"
namespace skarlygina
{
  ForwardList< std::string > getWords(std::istream&, char);
  template < typename Dict >
  Dict getDictionary(const ForwardList< std::string >& input)
  {
    Dict returnable;
    int key = 0;
    std::string value;
    for (auto i = (++input.cbegin()); i != input.cend(); ++i)
    {
      if (std::isdigit(i->front()) || (i->front() == '-'))
      {
        key = std::stoi(*i);
        continue;
      }
      value = *i;
      returnable.push(key, value);
    }
    return returnable;
  }
  template < typename Dict, typename AllDicts >
  AllDicts getDictsFromStream(std::istream& in)
  {
    if (!in.good())
    {
      throw std::logic_error("Unable to read from the stream");
    }
    AllDicts dicts;
    while (!in.eof())
    {
      auto words = getWords(in, '\n');
      if (words.isEmpty())
      {
        continue;
      }
      auto elem = getDictionary< Dict >(words);
      dicts.push(words.front(), elem);
    }
    return dicts;
  }
  template < typename Dict, typename AllDicts >
  void processCommand(std::istream& in, std::ostream& out, AllDicts& data)
  {
    auto words = skarlygina::getWords(in, '\n');
    if (words.isEmpty())
    {
      return;
    }
    if (words.getSize() < 2)
    {
      throw std::invalid_argument("Not enough args");
    }
    auto wordsIt = words.cbegin();
    std::string command = *(wordsIt++);
    std::string name = *(wordsIt++);
    if (command == "print")
    {
      skarlygina::print< AllDicts >(out, name, data);
      return;
    }
    if (words.getSize() < 4)
    {
      throw std::invalid_argument("Not enough args");
    }
    std::string lhs = *(wordsIt++);
    std::string rhs = *wordsIt;
    if (command == "complement")
    {
      data.push(name, skarlygina::complement< Dict, AllDicts >(lhs, rhs, data));
    }
    else if (command == "intersect")
    {
      data.push(name, skarlygina::intersect< Dict, AllDicts >(lhs, rhs, data));
    }
    else if (command == "union")
    {
      data.push(name, skarlygina::unite< Dict, AllDicts >(lhs, rhs, data));
    }
    else
    {
      throw std::invalid_argument("Unknown command");
    }
  }
}

#endif


