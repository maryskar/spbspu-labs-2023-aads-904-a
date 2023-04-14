#include <stdexcept>

template< typename T >
detail::ConstNodeIter< T >::ConstNodeIter():
  nodePtr(nullptr)
{}

template< typename T >
detail::ConstNodeIter< T >& detail::ConstNodeIter< T >::operator++()
{
  if (nodePtr) {
    nodePtr = nodePtr->next;
  }
  return *this;
}

template< typename T >
detail::ConstNodeIter< T > detail::ConstNodeIter< T >::operator++(int)
{
  ConstNodeIter< T > copy(*this);
  if (nodePtr) {
    nodePtr = nodePtr->next;
  }
  return copy;
}

template< typename T >
const T& detail::ConstNodeIter< T >::operator*() const
{
  if (!nodePtr) {
    throw std::runtime_error("Attempt to get value of nullptr NodeIter");
  }
  return nodePtr->data;
}

template< typename T >
const T* detail::ConstNodeIter< T >::operator->() const
{
  if (!nodePtr) {
    throw std::runtime_error("Attempt to get value of nullptr NodeIter");
  }
  return &(nodePtr->data);
}

template< typename T >
bool detail::ConstNodeIter< T >::operator==(const ConstNodeIter< T >& rhs) const
{
  return nodePtr == rhs.nodePtr;
}

template< typename T >
bool detail::ConstNodeIter< T >::operator!=(const ConstNodeIter< T >& rhs) const
{
  return !(*this == rhs);
}

template< typename T >
void detail::deleteNodes(Node< T >* head)
{
  while (head) {
    Node< T >* oldHead = head;
    head = head->next;
    delete oldHead;
  }
}

template< typename T >
std::pair< detail::Node< T >*, detail::Node< T >* > detail::duplicateNodes(const Node< T >* head)
{
  if (!head) {
    throw std::invalid_argument("Attempt to duplicate empty list");
  }
  Node< T >* const newHead = new Node< T >{head->data, nullptr};
  Node< T >* newTail = newHead;
  head = head->next;
  while (head != nullptr) {
    try {
      newTail->next = new Node< T >{head->data, nullptr};
    } catch (...) {
      deleteNodes(newHead);
      throw;
    }
    newTail = newTail->next;
    head = head->next;
  }
  return std::make_pair(newHead, newTail);
}
