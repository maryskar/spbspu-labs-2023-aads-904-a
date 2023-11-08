#include "commands.h"
#include <fstream>

std::string dmitriev::cutS(std::string& line)
{
  std::string res = "";
  std::size_t pos = line.find(' ');

  if (pos != std::string::npos)
  {
    res = line.substr(0, pos);
    line.erase(0, pos + 1);

    return res;
  }
  else if (line != "")
  {
    res = line;
    line = "";

    return res;
  }
  else
  {
    throw std::invalid_argument("incorrect args");
  }
}

void dmitriev::addBook(library& lib, std::string& line)
{
  std::string dirName = cutS(line);

  Book newBook{cutS(line), cutS(line), cutS(line), cutS(line), std::stol(cutS(line))};

  if (lib.at(dirName).find(newBook.key) != lib.at(dirName).end())
  {
    throw std::invalid_argument("book alrady exist");
  }
  lib.at(dirName)[newBook.key] = std::move(newBook);
}

size_t hammingDistance(const std::string& lhs, const std::string& rhs)
{
  size_t distance = 0;
  size_t length = std::min(lhs.length(), rhs.length());

  for (size_t i = 0; i < length; i++)
  {
    if (lhs[i] != rhs[i])
    {
      distance++;
    }
  }

  distance += std::abs(static_cast< int >(lhs.length() - rhs.length()));

  return distance;
}

dmitriev::ForwardList< dmitriev::Book > findBooks(const dmitriev::library& lib,
  const std::string& dir,
  const std::string& query,
  const std::string& parameter,
  size_t k)
{
  dmitriev::ForwardList< dmitriev::Book > result;
  const dmitriev::directory& books = lib.at(dir);

  typename dmitriev::directory::constIterator it = books.constBegin();
  for (; it != books.constEnd(); it++)
  {
    bool p1 = (parameter == "year" && std::to_string(it->value.year) == query);
    bool p2 = (parameter == "isbn" && it->value.isbn == query);

    std::string rhsStr = parameter == "title" ? it->value.title : it->value.author;
    size_t distance = hammingDistance(query, rhsStr);
    bool p3 = (parameter == "title" || parameter == "author") && distance <= k;

    if (p1 || p2 || p3)
    {
      result.pushFront(it->value);
    }
  }

  return result;
}

void dmitriev::deleteBook(library& lib, std::string& line)
{
  std::string dirName = cutS(line);
  std::string query = cutS(line);
  std::string parameter = cutS(line);

  const dmitriev::ForwardList< Book > result = findBooks(lib, dirName, query, parameter, 0);
  if (!result.isEmpty())
  {
    lib.at(dirName).erase(result.front().key);
  }
}

void dmitriev::copyBook(library& lib, std::string& line)
{
  std::string dirFrom = cutS(line);
  std::string dirTo = cutS(line);
  std::string query = cutS(line);
  std::string parameter = cutS(line);

  const dmitriev::ForwardList< Book > result = findBooks(lib, dirFrom, query, parameter, 0);
  if (!result.isEmpty())
  {
    Book newBook = result.front();
    if (lib.at(dirTo).find(newBook.key) != lib.at(dirTo).end())
    {
      throw std::invalid_argument("book alrady exist");
    }
    lib.at(dirTo)[newBook.key] = newBook;
  }
}

void dmitriev::createDirectory(library& lib, std::string& line)
{
  std::string dirName = cutS(line);
  if (lib.find(dirName) != lib.end())
  {
    throw std::invalid_argument("dir alrady exist");
  }
  lib[dirName];
}

void dmitriev::deleteDirectory(library& lib, std::string& line)
{
  std::string dirName = cutS(line);
  if (lib.find(dirName) == lib.end())
  {
    throw std::invalid_argument("dir not found");
  }

  lib.erase(dirName);
}

void dmitriev::combineDirectorys(library& lib, std::string& line)
{
  std::string newDirName = cutS(line);
  std::string lhsDirName = cutS(line);
  std::string rhsDirName = cutS(line);

  directory newDir = lib.at(lhsDirName);

  typename directory::constIterator it = lib.at(rhsDirName).begin();
  for (; it != lib.at(rhsDirName).end(); it++)
  {
    if (lib.at(lhsDirName).find(it->key) == lib.at(lhsDirName).end())
    {
      newDir.insert({it->key, it->value});
    }
  }

  if (lib.find(newDirName) != lib.end())
  {
    throw std::invalid_argument("dir alrady exist");
  }
  lib[newDirName] = newDir;
}

void dmitriev::downloadDirectory(library& lib, std::string& line)
{
  std::string dirName = cutS(line);
  std::string fileName = cutS(line);

  std::ifstream file(fileName);
  if (!file.is_open())
  {
    throw std::invalid_argument("incorrect file name");
  }

  directory newDir;
  Book newBook;
  while (!file.eof())
  {
    file >> newBook;
    newDir[newBook.key] = newBook;
  }

  if (lib.find(dirName) != lib.end())
  {
    throw std::invalid_argument("dir alrady exist");
  }
  lib[dirName] = newDir;
}

void printBook(const dmitriev::Book& book, std::ostream& out)
{
  out << "key: " << book.key << '\n';
  out << "title: " << book.title << '\n';
  out << "author: " << book.author << '\n';
  out << "isbn: " << book.isbn << '\n';
  out << "year: " << book.year;
}

void dmitriev::printFindedBooks(const library& lib, std::string& line, std::ostream& out)
{
  std::string dirName = cutS(line);
  std::string query = cutS(line);
  std::string parameter = cutS(line);
  const dmitriev::ForwardList< dmitriev::Book > result = findBooks(lib, dirName, query, parameter, std::stol(cutS(line)));

  typename dmitriev::ForwardList< dmitriev::Book >::constIterator it = result.constBegin();
  if (it == result.constEnd())
  {
    return;
  }
  printBook(*it++, out);
  while (it != result.constEnd())
  {
    out << "\n\n";
    printBook(*it++, out);
  }
}

void dmitriev::printDirectory(const library& lib, std::string& line, std::ostream& out)
{
  std::string dirName = cutS(line);

  typename directory::constIterator it = lib.at(dirName).constBegin();
  if (it == lib.at(dirName).constEnd())
  {
    return;
  }
  printBook(it->value, out);
  it++;
  for (; it != lib.at(dirName).constEnd(); it++)
  {
    out << "\n\n";
    printBook(it->value, out);
  }
}

void dmitriev::unloadDirectory(const library& lib, std::string& line, std::ostream& out)
{
  std::string dirName = cutS(line);
  std::string fileName = cutS(line);

  std::ofstream file(fileName);
  if (!file.is_open())
  {
    throw std::invalid_argument("incorrect file name");
  }

  typename directory::constIterator it = lib.at(dirName).constBegin();
  for (; it != lib.at(dirName).constEnd(); it++)
  {
    file << it->value << '\n';
  }

}
