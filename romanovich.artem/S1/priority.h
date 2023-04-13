#ifndef PRIORITY_H
#define PRIORITY_H
#include <string>
namespace romanovich
{
  class Priority
  {
  public:
    explicit Priority(const std::string &op);
    bool operator>=(const Priority &op) const;
  private:
    static size_t getPriority(const std::string &basicString);
    size_t priority_;
  };
  inline Priority::Priority(const std::string &op):
    priority_(Priority::getPriority(op))
  {
  }
}
#endif
