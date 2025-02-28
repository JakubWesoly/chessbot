#ifndef MENU_HPP
#define MENU_HPP

#include <string>
#include "Board.hpp"

namespace Menu
{
  void init();
  std::string getMove();
  void printBoard(const Board::Board &board);
} // namespace Menu

#endif // MENU_HPP