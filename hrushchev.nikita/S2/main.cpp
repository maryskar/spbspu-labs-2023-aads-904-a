#include "forwardlist.hpp"
#include <list.hpp>
#include <iostream>

int main()
{
  ForwardList< int > my_list;
  my_list.head_ = nullptr;
  my_list.pushFront(1);
  my_list.pushFront(2);
  my_list.pushFront(3);
  my_list.pushFront(4);
  my_list.pushFront(5);
  my_list.pushFront(6);
  List< int >* temp = my_list.head_;
  while (temp->next_ != nullptr)
  {
    std::cout << temp->data_ << " " <<  temp->next_ << "\n";
    temp = temp->next_;
  }
  std::cout << temp->data_ << " " <<  temp->next_ << "\n";


  my_list.clear();
  List< int >* temp2 = my_list.head_;
  while (temp2->next_ != nullptr)
  {
    std::cout << temp2->data_ << " " <<  temp2->next_ << "\n";
    temp2 = temp2->next_;
  }
  std::cout << temp2->data_ << " " <<  temp2->next_ << "\n";
}
