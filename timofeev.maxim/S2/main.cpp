#include <iostream>
#include <fstream>
#include <Dictionary.h>
#include <commands/commandSet.h>
#include <Errors.h>
#include <inDict.h>
int main(int argc, char *argv[])
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
  using dictionary = timofeev::Dictionary< size_t, std::string, std::less<> >;
  using dictOfDicts = timofeev::Dictionary< std::string, dictionary, std::less<> >;
  using command = timofeev::Dictionary< std::string, void (*)(std::istream&, dictOfDicts&, dictionary) >;
  dictionary lildict;
  dictOfDicts dict;
  dict = timofeev::inDict< dictOfDicts, dictionary >(inFile, dict);
  command commands;
  commands = timofeev::cmdSet< command, dictionary >();
  while (!std::cin.eof())
  {
    try
    {
      std::string firstPart = "";
      std::cin >> firstPart;
      if (!std::cin)
      {
        break;
      }
      if (firstPart == "print")
      {
        timofeev::doPrint< dictOfDicts >(std::cin, dict, std::cout);
      }
      else
      {
        commands.at(firstPart)(std::cin, dict, lildict);
      }
    }
    catch (const std::invalid_argument &e)
    {
      timofeev::printInvalid(std::cout);
      std::cout << "\n";
      break;
    }
    catch (const std::out_of_range &e)
    {
      timofeev::printEmpty(std::cout);
      std::cout << "\n";
      break;
    }
  }
  return 0;
}
