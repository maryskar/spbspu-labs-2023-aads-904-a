#include "reading_dicts.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include "dictionary.h"
#include "forwardlist.h"
#include "commands.h"

skarlygina::Dictionary< int, std::string > getDict(const skarlygina::ForwardList< std::string >& in)
{
  skarlygina::Dictionary< int, std::string > ok_dict;
  int key = 0;
  std::string string;
  for (auto i = (++in.cbegin()); i != in.cend(); ++i)
  {
    if (std::isdigit(i->front()))
    {
      key = std::stoi(*i);
      continue;
    }
    string = *i;
    ok_dict.push(key, string);
  }
  return ok_dict;
}

skarlygina::Dictis skarlygina::getDictis(std::istream& in)
{
  if (!in.good())
    throw std::logic_error("Unable to read!\n");
  Dictis dictis;
  while (!in.eof())
  {
    auto words = getWords(in, '\n');
    if (words.isEmpty())
      continue;
    Dictionary< int, std::string > elem = getDict(words);
    dictis.push(words.front(), elem);
  }
  return dictis;
}

skarlygina::ForwardList< std::string > skarlygina::getWords(std::istream& in, char char_)
{
  auto words = ForwardList< std::string >();
  char next = in.get();
  while ((next != char_) && !in.eof())
  {
    std::string elem;
    while (!std::isspace(next) && (next != char_) && !in.eof())
    {
      elem.push_back(next);
      next = in.get();
    }
    words.pushBack(elem);
    next = (next == char_) ? next : in.get();
  }
  return words;
}
