#ifndef WORDENTRY_H
#define WORDENTRY_H
#include <string>
#include <vector>
namespace romanovich
{
  struct WordEntry
  {
    enum class Level
    {
      beginner,
      intermediate,
      advanced
    };
    std::string word;
    std::vector< std::string > translations;
    Level level;
    bool operator==(const WordEntry &rhs) const;
  };
}
#endif
