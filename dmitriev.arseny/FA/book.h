#ifndef BOOK_H
#define BOOK_H

#include <string>

namespace dmitriev
{
  struct Book
  {
    std::string key;
    std::string title;
    std::string author;
    std::string isbn;

    size_t year;
  };

  std::istream& operator>>(std::istream& inp, Book& data);
  std::ostream& operator<<(std::ostream& out, const Book& data);
}

#endif
