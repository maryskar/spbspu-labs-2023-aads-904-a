#ifndef OPERATION_H
#define OPERATION_H
#include <string>
class Operation
{
public:
  explicit Operation(const std::string &op);
  bool operator>=(const Operation &op) const;
private:
  size_t getPriority(const std::string &basicString);
  size_t priority_;
};

inline Operation::Operation(const std::string &op):
  priority_(Operation::getPriority(op))
{
}
#endif
