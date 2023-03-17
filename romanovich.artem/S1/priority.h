#ifndef PRIORITY_H
#define PRIORITY_H
#include <string>
class Priority
{
public:
  explicit Priority(const std::string &op);
  bool operator>=(const Priority &op) const;
private:
  size_t getPriority(const std::string &basicString);
  size_t priority_;
};
inline Priority::Priority(const std::string &op):
  priority_(Priority::getPriority(op))
{
}
#endif
