#ifndef TYPE_OPERATION_H
#define TYPE_OPERATION_H
namespace tarasenko
{
  class Operation
  {
  public:
   Operation(char op);
   char getValue() const;
   bool operator<=(const Operation& rhs) const;
  private:
   char value_;
   int priority_;
  };
};
#endif
