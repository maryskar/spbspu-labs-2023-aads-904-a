#include <iostream>
#include <functional>
#include "commands.h"

int main()
{
  using cmd = std::function< void(dmitriev::library&, std::string&) >;
  using cCmd = std::function< void(const dmitriev::library&, std::string&, std::ostream&) >;

  dmitriev::UnorderedMap< std::string, cmd > cmds;
  dmitriev::UnorderedMap< std::string, cCmd > cCmds;

  cmds["ADD_BOOK"] = dmitriev::addBook;
  cmds["DELETE_BOOK"] = dmitriev::deleteBook;
  cmds["COPY_BOOK"] = dmitriev::copyBook;
  cmds["CREATE_DIRECTORY"] = dmitriev::createDirectory;
  cmds["DELETE_DIRECTORY"] = dmitriev::deleteDirectory;
  cmds["COMBINE_TWO_DIRECTORIES"] = dmitriev::combineDirectorys;
  cmds["DOWNLOAD_FROM_FILE"] = dmitriev::downloadDirectory;

  cCmds["FIND_BOOK"] = dmitriev::printFindedBooks;
  cCmds["OUTPUT_LIST_OF_ALL_BOOKS"] = dmitriev::printDirectory;
  cCmds["SAVE_TO_FILE"] = dmitriev::unloadDirectory;


  dmitriev::library lib;
  std::string line = "";
  while (std::getline(std::cin, line))
  {
    if (line.empty())
    {
      continue;
    }
    std::string cmdName = dmitriev::cutS(line);

    try
    {
      try
      {
        cmds.at(cmdName)(lib, line);
      }
      catch (const std::exception&)
      {
        cCmds.at(cmdName)(lib, line, std::cout);
        std::cout << '\n';
      }
    }
    catch (const std::exception& e)
    {
      std::cerr << e.what() << '\n';
    }
  }


  return 0;
}
