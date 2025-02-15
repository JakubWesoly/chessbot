#include <iostream>

#include "Program.hpp"

#include "Menu.hpp"
#include "Move.hpp"
#include "Brain.hpp"

namespace Program
{
  void run()
  {
    Brain::Brain bot;

    Menu::init();

    Menu::print_board(bot.realBoard);

    bool isPlayerBlocked = true;

    while (true)
    {
        std::string moveStr = Menu::get_move();

        std::cout << moveStr << std::endl;

        Move::Move move(moveStr);

        std::cout << move.to << std::endl;

        bool isValidMove = bot.makeRealMove(move);

        std::cout << "Your move is: " << (isValidMove ? "valid" : "invalid") << std::endl;
        

      if(isValidMove) {
        Move::Move botsMove = bot.findBestMove();

        std::cout
            << "Evaluation: " << bot.evaluatePosition() << std::endl
            << "Bot's move: " << botsMove.toString() << std::endl;

        bot.makeRealMove(botsMove);
      }


      Menu::print_board(bot.realBoard);

      isPlayerBlocked = false;
    }
  }
} // namespace Program
