#include "Menu.hpp"

#include <iostream>

namespace Menu
{
  void init()
  {
    std::cout << " _______  __   __  _______  _______  _______  _______  _______  _______ "
              << "\n"
              << "|       ||  | |  ||       ||       ||       ||  _    ||       ||       |"
              << "\n"
              << "|       ||  |_|  ||    ___||  _____||  _____|| |_|   ||   _   ||_     _|"
              << "\n"
              << "|       ||       ||   |___ | |_____ | |_____ |       ||  | |  |  |   |  "
              << "\n"
              << "|      _||       ||    ___||_____  ||_____  ||  _   | |  |_|  |  |   |  "
              << "\n"
              << "|     |_ |   _   ||   |___  _____| | _____| || |_|   ||       |  |   |  "
              << "\n"
              << "|_______||__| |__||_______||_______||_______||_______||_______|  |___|  "
              << "\n";
  }

  std::string get_move()
  {
    std::string move;
    std::cout << "Enter a move: ";
    std::cin >> move;
    return move;
  }

  void print_board(const Board::Board &board)
  {
    std::cout << (board.isWhiteTurn ? "White" : "Black") << " turn\n\n";
    std::cout << std::endl
              << "    a  b  c  d  e  f  g  h " << std::endl;
    std::cout << "  ---------------------------" << std::endl;
    for (int i = 0; i < 8; i++)
    {
      std::cout
          << " ";
      std::cout << 8 - i << "| ";
      for (int j = 0; j < 8; j++)
      {
        auto tileIndex = 56 - i * 8 + j;
        auto tile = board.board[tileIndex];

        if (tile == 0)
          std::cout << "  ";

        else if (tile & 1)
          std::cout << "B";

        else
          std::cout << "W";

        if (tile & 2)
          std::cout << "P";

        else if (tile & 8)
          std::cout << "B";

        else if (tile & 4)
          std::cout << "N";

        else if (tile & 16)
          std::cout << "R";

        else if (tile & 32)
          std::cout << "Q";

        else if (tile & 64)
          std::cout << "K";

        std::cout << " ";
      }
      std::cout << "|" << std::endl;
    }
    std::cout << "  ---------------------------" << std::endl
              << std::endl;
  }
} // namespace Menu