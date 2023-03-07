#ifndef SPBSPU_LABS_2023_AADS_904_A_PART_H
#define SPBSPU_LABS_2023_AADS_904_A_PART_H
#include <string>
namespace dimkashelk
{
  struct part
  {
    explicit part(std::string str);
    explicit part(long long number);
    bool isDigit_;
    union
    {
      long long operand_;
      char operator_;
    } element_{};
  };
}
#endif
