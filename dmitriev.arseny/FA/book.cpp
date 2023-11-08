#include "book.h"
#include <iostream>
#include "customtypes.h"


std::istream& dmitriev::operator>>(std::istream& inp, Book& data)
{
  std::istream::sentry sentry(inp);
  if (!sentry)
  {
    return inp;
  }

  inp >> LableIO{"@Book"} >> SeparatorIO{'{'};

  Book input;
  std::getline(inp, input.key, ',');
  for (size_t i = 0; i < 4; i++)
  {
    if (i > 0)
    {
      inp >> SeparatorIO{','};
    }
    std::string field = "";
    inp >> field;


    if (field == "title")
    {
      inp >> SeparatorIO{'='} >> StringI{input.title};
    }
    else if (field == "author")
    {
      inp >> SeparatorIO{'='} >> StringI{input.author};
    }
    else if (field == "isbn")
    {
      inp >> SeparatorIO{'='} >> StringI{input.isbn};
    }
    else if (field == "year")
    {
      inp >> SeparatorIO{'='} >> input.year;
    }
    else
    {
      inp.setstate(std::ios::failbit);
    }
    if (!sentry)
    {
      return inp;
    }
  }
  inp >> SeparatorIO{'}'};

  if (inp)
  {
    data = input;
  }

  return inp;
}

std::ostream& dmitriev::operator<<(std::ostream& out, const Book& data)
{
  out << "@Book{" << data.key << ",\n";
  out << " " << "author = " << StringO{data.author} << ",\n";
  out << " " << "title = " << StringO{data.title} << ",\n";
  out << " " << "year = " << data.year << ",\n";
  out << " " << "isbn = " << StringO{data.isbn} << "\n";
  out << "}";

  return out;
}
