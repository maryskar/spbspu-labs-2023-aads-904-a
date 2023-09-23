#include "getDicts.h"
#include <stdexcept>
#include <string>
#include "commands.h"

namespace chulkov {
  Dictionary< int, std::string > getDict(const FrdList< std::string >& in)
  {
    Dictionary< int, std::string > returnable;
    int key = 0;
    std::string string;
    for (ForwardConstIter< std::string > i = (++in.cbegin()); i != in.cend(); ++i) {
      if (std::isdigit(i->front())) {
        key = std::stoi(*i);
        continue;
      }
      string = *i;
      returnable.push(key, string);
    }
    return returnable;
  }

  Dicts getDicts(std::istream& in)
  {
    if (!in.good()) {
      throw std::logic_error("Unable to read!\n");
    }
    Dicts dicts;
    while (!in.eof()) {
      auto words = getWords(in, '\n');
      if (words.isEmpty()) {
        continue;
      }
      Dictionary< int, std::string > elem = getDict(words);
      dicts.push(words.front(), elem);
    }
    return dicts;
  }

  FrdList< std::string > getWords(std::istream& in, char char_)
  {
    auto words = FrdList< std::string >();
    char next = in.get();
    while ((next != char_) && !in.eof()) {
      std::string elem;
      while (!std::isspace(next) && (next != char_) && !in.eof()) {
        elem.push_back(next);
        next = in.get();
      }
      words.pushBack(elem);
      next = (next == char_) ? next : in.get();
    }
    return words;
  }
}
