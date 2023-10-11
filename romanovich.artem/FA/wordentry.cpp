#include "wordentry.h"
bool romanovich::WordEntry::operator==(const WordEntry &rhs) const
{
  return word == rhs.word;
}
