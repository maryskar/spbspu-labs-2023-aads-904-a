#include "parsing.h"
void romanovich::splitString(std::vector< std::string > &elems, const std::string &line, char del)
{
  std::string word;
  size_t startPos = 0;
  size_t endPos = line.find(del);
  while (endPos != std::string::npos)
  {
    word = line.substr(startPos, endPos - startPos);
    elems.push_back(word);
    startPos = endPos + 1;
    endPos = line.find(del, startPos);
  }
  word = line.substr(startPos, endPos);
  elems.push_back(word);
}
