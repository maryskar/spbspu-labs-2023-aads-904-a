#ifndef WORDENTRY_H
#define WORDENTRY_H
#include <string>
#include <vector>
struct WordEntry
{
  std::string word;
  std::vector< std::string > translations;
};
#endif
