#ifndef IOSTREAMOVERLOADS_H
#define IOSTREAMOVERLOADS_H
#include <ios>
#include <iostream>
#include <string>
#include <dictionary.h>
#include <AVL.h>

namespace mashkin
{
  std::istream& operator>>(std::istream& inp, Dictionary< int, std::string >& dict);
  std::istream& operator>>(std::istream& inp, Dictionary< std::string, Dictionary< int, std::string > >& dicts);
  std::ostream& operator<<(std::ostream& out, const Dictionary< int, std::string >& dicts);

  std::istream& operator>>(std::istream& inp, AVL< int, std::string >& dict);
  std::istream& operator>>(std::istream& inp, AVL< std::string, AVL< int, std::string > >& dicts);
  std::ostream& operator<<(std::ostream& out, const AVL< int, std::string >& dicts);
}
#endif
