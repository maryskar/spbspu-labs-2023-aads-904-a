#ifndef SPBSPU_LABS_2023_AADS_904_A_PART_H
#define SPBSPU_LABS_2023_AADS_904_A_PART_H
#include <string>
namespace dimkashelk
{
  union part
  {
    bool isDigit_ = false;
    int operand_;
    char operator_;
  };
  part makePart(std::string str);
}
#endif
