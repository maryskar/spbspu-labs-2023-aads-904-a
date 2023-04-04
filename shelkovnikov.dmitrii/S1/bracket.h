#ifndef SPBSPU_LABS_2023_AADS_904_A_BRACKET_H
#define SPBSPU_LABS_2023_AADS_904_A_BRACKET_H
namespace dimkashelk
{
  class Bracket
  {
  public:
    Bracket();
    Bracket(const Bracket &bracket) = default;
    Bracket(Bracket &&bracket) = default;
    explicit Bracket(char c);
    Bracket &operator=(const Bracket &bracket) = default;
    Bracket &operator=(Bracket &&bracket) = default;
    bool isOpen() const;
    bool isClose() const;
    static bool isBracket(char c);
  private:
    char bracket_;
  };
}
#endif
