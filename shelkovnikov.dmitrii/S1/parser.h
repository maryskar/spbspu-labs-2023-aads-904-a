#ifndef SPBSPU_LABS_2023_AADS_904_A_PARSER_H
#define SPBSPU_LABS_2023_AADS_904_A_PARSER_H
#include <string>
#include <cstddef>
namespace dimkashelk
{
  class Parser
  {
  public:
    explicit Parser(std::string str);
    std::string operator()();
    bool hasNext();
  private:
    std::string::iterator begin;
    std::string::iterator end;
  };
}
#endif
