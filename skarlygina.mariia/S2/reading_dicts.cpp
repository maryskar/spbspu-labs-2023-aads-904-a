#include "reading_dicts.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <sstream>
#include "dictionary.h"
#include "forwardlist.h"
#include "commands.h"

skarlygina::Dictionary< std::string, skarlygina::Dictionary< int, std::string > > skarlygina::getDictis(std::istream& in)
{
  if (!in.good())
  {
    throw std::logic_error("Unable to read!\n");
  }
  Dictionary< std::string, Dictionary< int, std::string > > dictis;
  while (!in.eof())
  {
    auto words = getWords(in, '\n');
    if (words.isEmpty())
    {
      continue;
    }
    Dictionary< int, std::string > elem;
    int key = 0;
    std::string string;
    for (auto i = (++words.cbegin()); i != words.cend(); ++i)
    {
      if (std::isdigit(i->front()))
      {
        key = std::stoi(*i);
        continue;
      }
      string = *i;
      elem.push(key, string);
    }
    dictis.push(words.front(), elem);
  }
  return dictis;
}

skarlygina::ForwardList< std::string > skarlygina::getWords(std::istream& in, char char_)
{
  auto words = ForwardList< std::string >();
  std::string elem;
  while (std::getline(in, elem, char_))
  {
    std::istringstream iss(elem);
    std::string word;
    while (iss >> word)
    {
      words.pushBack(word);
    }
  }
  return words;
}
