/*
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "dict.h"
void
printDictionary(const Dictionary< std::string, Dictionary< int, std::string > > &dictionary)
{
  for (const auto &entry: dictionary)
  {
    std::cout << "Dictionary name: " << entry.first << "\n";
    const auto &dictData = entry.second;
    for (const auto &item: dictData)
    {
      std::cout << "Key: " << item.first << ", Value: " << item.second << "\n";
    }
    std::cout << "\n";
  }
}
void splitString(std::vector< std::string > &elems, const std::string &line, char del)
{
  std::string word;
  size_t startPos = 0;
  size_t endPos = line.find(del);
  while (endPos != std::string::npos)
  {
    word = line.substr(startPos, endPos - startPos);
    elems.push_back(word);
    startPos = endPos + 1;
    endPos = line.find(del, startPos);
  }
  word = line.substr(startPos, endPos);
  elems.push_back(word);
}
int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    std::cerr << "No file provided.\n";
    return 1;
  }
  std::ifstream input(argv[1]);
  if (!input)
  {
    std::cerr << "Cannot open file.\n";
    return 1;
  }
  using dict_type = Dictionary< int, std::string >;
  using dict_value_type = std::pair< int, std::string >;
  using container_type = Dictionary< std::string, dict_type >;
  using container_value_type = std::pair< std::string, dict_type >;
  container_type dictionary;
  std::string line;
  while (std::getline(input, line))
  {
    std::vector< std::string > lineWords;
    splitString(lineWords, line, ' ');
    std::string dictName = lineWords[0];
    dict_type dictData;
    for (size_t i = 1; i < lineWords.size(); i += 2)
    {
      int key = std::stoi(lineWords[i]);
      std::string val = lineWords[i + 1];
      //std::cout << key << " " << val << "\n";
      dictData.emplace(dict_value_type(key, val));
      auto ptr = dictData.data_.begin_;
      while (ptr)
      {
        std::cout << ptr->data_.first << ' '
                  << ptr->data_.second << ' ';
        ptr = ptr->next_;
      }
      //std::cout << '\n';
    }
    dictionary.emplace(container_value_type(dictName, dictData));
    //printDictionary(dictionary);
    //std::cout << "\n";
  }
  printDictionary(dictionary);
  */
/*std::cout << "@";
  std::cout << sizeof dictionary.data_.begin_->data_;
  std::cout << "@";
  auto ptr = pt.second.data_.begin_;
 while (ptr)
 {
   std::cout << ptr->data_.second << ' ';
   std::cout << ptr->data_.first;
   ptr = ptr->next_;
 }*//*

}
*/
//----------------------------------------
#include <iostream>
#include "forwardlist.h"
int main()
{
  ForwardList< int > myList;

  // Add elements to the beginning of the list
  myList.push_front(1);
  myList.push_front(2);
  myList.push_front(3);

  // Iterate over the elements using iterators
  std::cout << "List: ";
  for (const auto &value: myList)
  {
    std::cout << value << " ";
  }
  std::cout << std::endl;

  // Check if the list is empty
  std::cout << "List is empty: " << std::boolalpha << myList.empty() << std::endl;

  // Insert an element after a specified position
  ForwardList< int >::iterator it = myList.begin();
  ++it; // Move to the second element
  myList.insert_after(it, 10); // Insert 10 after the second element

  // Print the list after insertion
  std::cout << "List after insertion: ";
  for (const auto &value: myList)
  {
    std::cout << value << " ";
  }
  std::cout << std::endl;


  // Erase an element after a specified position
  myList.erase_after(ConstForwardListIterator< int >(it));

  // Print the list after erasing an element
  std::cout << "List after erasing: ";
  for (const auto &value: myList)
  {
    std::cout << value << " ";
  }
  std::cout << std::endl;


  // Resize the list
  myList.resize(5, 8); // Increase the size of the list to 5 and fill the new elements with zeros

  // Print the list after resizing
  std::cout << "List after resizing: ";
  for (const auto &value: myList)
  {
    std::cout << value << " ";
  }
  std::cout << std::endl;


  // Reverse the order of elements in the list
  myList.reverse();

  // Print the list after reversing the order
  std::cout << "List after reversing the order: ";
  for (const auto &value: myList)
  {
    std::cout << value << " ";
  }
  std::cout << std::endl;

  // Insert an element after a specified position using emplace_after()
  ForwardList< int >::const_iterator it1 = myList.cbegin();
  ++it1; // Move to the second element
  myList.emplace_after(it1, 10); // Insert 10 after the second element using emplace_after()

  // Print the list after insertion
  std::cout << "List after insertion: ";
  for (const auto &value: myList)
  {
    std::cout << value << " ";
  }
  std::cout << std::endl;

  // Remove the first element from the list using pop_front()
  myList.pop_front();

  // Print the list after removing an element
  std::cout << "List after removal: ";
  for (const auto &value: myList)
  {
    std::cout << value << " ";
  }
  std::cout << std::endl;

  // Clear all elements from the list
  myList.clear();

  // Check if the list is empty after clearing
  std::cout << "List is empty: " << std::boolalpha << myList.empty() << std::endl;
  return 0;
}
