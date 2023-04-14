#ifndef PRIORITY_H
#define PRIORITY_H
#include <string>
namespace romanovich
{
  class Priority
  {
  public:
    explicit Priority(const std::string &op);
    bool operator<(const Priority &op) const;
  private:
    size_t priority_;
    static size_t getPriority(const std::string &basicString);
  };
  inline Priority::Priority(const std::string &op):
    priority_(Priority::getPriority(op))
  {
  }
}
#endif
