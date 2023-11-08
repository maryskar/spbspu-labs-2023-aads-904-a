#ifndef STREAMPROCESSING_H
#define STREAMPROCESSING_H
#include <string>
#include <iosfwd>
#include <functional>
#include <getDicts.h>
#include <ForwardList.h>
#include "commands.h"

namespace chulkov
{
  template < typename Dict >
  Dict getDictionary(const ForwardList< std::string >& input)
  {
    Dict returnable;
    int key = 0;
    std::string value;
    for (auto i = (++input.cbegin()); i != input.cend(); ++i) {
      if (std::isdigit(i->front()) || (i->front() == '-')) {
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
    if (!in.good()) {
      throw std::logic_error("Unable to read from the stream");
    }
    AllDicts dicts;
    while (!in.eof()) {
      auto words = getWords(in, '\n');
      if (words.isEmpty()) {
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
    ForwardList< std::string > words = getWords(in, '\n');
    if (words.isEmpty()) {
      return;
    }

    int wordCount = 0;
    for (chulkov::ForwardConstIter< std::string > it = words.cbegin(); it != words.cend(); ++it) {
      ++wordCount;
    }

    if (wordCount < 2) {
      throw std::invalid_argument("You need more args\n");
    }
    auto wordsIt = words.cbegin();
    std::string command = *(wordsIt++);
    std::string name = *(wordsIt++);
    if (command == "print") {
      print< AllDicts >(out, name, data);
      return;
    }
    if (wordCount < 4) {
      throw std::invalid_argument("Not enough args");
    }
    std::string lhs = *(wordsIt++);
    std::string rhs = *wordsIt;
    if (command == "complement") {
      data.push(name, complement< Dict, AllDicts >(lhs, rhs, data));
    }
    else if (command == "intersect") {
      data.push(name, intersect< Dict, AllDicts >(lhs, rhs, data));
    }
    else if (command == "union") {
      data.push(name, unite< Dict, AllDicts >(lhs, rhs, data));
    }
    else {
      throw std::invalid_argument("Unknown command");
    }
  }
}

#endif
