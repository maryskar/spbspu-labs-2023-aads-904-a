#ifndef SPBSPU_LABS_2023_AADS_904_A_CONTAINER_H
#define SPBSPU_LABS_2023_AADS_904_A_CONTAINER_H
namespace dimkashelk
{
  template< typename T >
  class Container
  {
  public:
    virtual void push(T rhs) = 0;
    virtual T drop() = 0;
    virtual bool empty() const = 0;
  };
}
#endif
