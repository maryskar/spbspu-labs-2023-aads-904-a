#ifndef PRIORITY_H
#define PRIORITY_H
#include <string>
#include "expressionpart.h"
namespace romanovich
{
  class Priority
  {
  public:
    explicit Priority(operations_t op):
      priority_(Priority::getPriority(op))
    {
    }
    bool operator<(const Priority &op) const;
  private:
    size_t priority_;
    static size_t getPriority(const operations_t &operation);
  };
}
#endif
