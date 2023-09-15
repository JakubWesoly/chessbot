#ifndef MENU_HPP
#define MENU_HPP

#include <string>
#include "Board.hpp"

namespace Menu
{
  void init();
  std::string get_move();
  void print_board(const Board::Board &board);
} // namespace Menu

#endif // MENU_HPP