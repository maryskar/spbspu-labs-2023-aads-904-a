template< typename T >
void odintsov::deleteNodes(Node< T >* head)
{
  while (head != nullptr) {
    Node< T >* oldHead = head;
    head = head->next;
    delete oldHead;
  }
}

template< typename T >
std::pair< odintsov::Node< T >*, odintsov::Node< T >* > odintsov::duplicateNodes(const Node< T >* head)
{
  Node< T >* const newHead = new Node< T >{head->data, nullptr};
  Node< T >* newTail = newHead;
  while (head != nullptr) {
    head = head->next;
    try {
      newTail->next = new Node< T >{head->data, nullptr};
    } catch (...) {
      deleteNodes(newHead);
      throw;
    }
    newTail = newTail->next;
  }
  return std::make_pair(newHead, newTail);
}
