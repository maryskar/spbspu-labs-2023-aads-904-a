#ifndef OPERATIONS_H
#define OPERATIONS_H
#include <string>
class Operation
{
public:
  explicit Operation(const std::string &op);
  bool operator<=(const Operation &op) const;
private:
  size_t getPriority(const std::string &basicString);
  bool isGreaterPriority(const Operation &lhs, const Operation &rhs);
  std::string operation_;
  size_t priority_;
};
Operation::Operation(const std::string &op):
  operation_(op),
  priority_(Operation::getPriority(op))
{
}
#endif
