#ifndef SPBSPU_LABS_2023_AADS_904_A_PARENTHESIS_H
#define SPBSPU_LABS_2023_AADS_904_A_PARENTHESIS_H
namespace dimkashelk
{
  class Parenthesis
  {
  public:
    Parenthesis() = default;
    Parenthesis(const Parenthesis &parenthesis) = default;
    Parenthesis(Parenthesis &&parenthesis) = default;
    explicit Parenthesis(char c);
    ~Parenthesis() = default;
    Parenthesis &operator=(const Parenthesis &parenthesis) = default;
    Parenthesis &operator=(Parenthesis &&parenthesis) = default;
    bool isOpen() const;
    bool isClose() const;
  private:
    char parenthesis_;
    bool isParenthesis() const;
  };
}
#endif
