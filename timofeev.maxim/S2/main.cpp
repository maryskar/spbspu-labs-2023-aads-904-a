#include <iostream>
#include <fstream>
#include <limits>
int main(int argc, char **argv)
{
  if (argc != 2)
  {
    std::cerr << "Error\n";
    return 1;
  }
  std::ifstream inFile;
  if (argc == 2)
  {
    inFile.open(argv[1]);
    if (!inFile.is_open())
    {
      std::cerr << "File error" << "\n";
      return 1;
    }
  }
  std::vector< timofeev::Polygon > polygon;
  using inIter = std::istream_iterator< timofeev::Polygon >;
  constexpr auto maxSize = std::numeric_limits< std::streamsize >::max();
  while (!inFile.eof())
  {
    std::copy(inIter(inFile), inIter(), std::back_inserter(polygon));
    if (inFile.fail())
    {
      inFile.clear();
      inFile.ignore(maxSize, '\n');
    }
  }
  std::map< std::string, void (*)(std::istream&, const std::vector< timofeev::Polygon >&) > commands;
  std::string firstPart;
  timofeev::dictionary(commands);
  while (!std::cin.eof())
  {
    try
    {
      std::cin >> firstPart;
      if (commands.count(firstPart) == 0)
      {
        timofeev::printError(std::cout);
      }
      else
      {
        commands[firstPart](std::cin, polygon);
      }
    }
    catch (std::logic_error &e)
    {
      timofeev::printError(std::cout);
      std::cin.ignore(maxSize, '\n');
    }
    catch (const std::runtime_error & e)
    {
      break;
    }
  }
  if (std::cin.fail())
  {
    std::cin.clear();
    std::cin.ignore(maxSize, '\n');
  }
  return 0;
}
