#ifndef SPBSPU_LABS_2023_AADS_904_A_PART_H
#define SPBSPU_LABS_2023_AADS_904_A_PART_H
#include <string>
namespace dimkashelk
{
  struct part
  {
    bool isDigit_;
    union
    {
      long long operand_;
      char operator_;
    } element_;
  };
  part makePart(std::string str);
  part makePart(long long number);
}
#endif
