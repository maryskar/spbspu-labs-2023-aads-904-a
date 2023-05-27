#ifndef SPBSPU_LABS_2023_AADS_904_A_PARENTHESIS_H
#define SPBSPU_LABS_2023_AADS_904_A_PARENTHESIS_H
namespace dimkashelk
{
  class Parenthesis
  {
  public:
    explicit Parenthesis(char c);
    bool isOpen() const;
    bool isClose() const;
    static bool isParenthesis(char c);
  private:
    char parenthesis_;
  };
}
#endif
