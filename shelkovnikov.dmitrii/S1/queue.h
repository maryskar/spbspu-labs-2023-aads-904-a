#ifndef SPBSPU_LABS_2023_AADS_904_A_QUEUE_H
#define SPBSPU_LABS_2023_AADS_904_A_QUEUE_H
namespace dimkashelk
{
  template <typename T>
  class Queue
  {
  public:
    Queue();
    void push(T rhs);
    T drop();
  private:
    T *data_;
  };
}
#endif
