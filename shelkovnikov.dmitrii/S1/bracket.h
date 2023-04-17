#ifndef SPBSPU_LABS_2023_AADS_904_A_BRACKET_H
#define SPBSPU_LABS_2023_AADS_904_A_BRACKET_H
namespace dimkashelk
{
  class Bracket
  {
  public:
    explicit Bracket(char c);
    bool isOpen() const;
    bool isClose() const;
  private:
    char bracket_;
    bool isBracket() const;
  };
}
#endif
