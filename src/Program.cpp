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

    Menu::printBoard(bot.realBoard);

    while (true)
    {
        std::string moveStr = Menu::getMove();

        std::cout << moveStr << "\n";

        Move::Move move(moveStr);

        std::cout << move.to << "\n";

        bool isValidMove = bot.makeRealMove(move);

        std::cout << "Your move is: " << (isValidMove ? "valid" : "invalid") << "\n";
        

      if(isValidMove) {
        Move::Move botsMove = bot.findBestMove();

        std::cout
            << "Evaluation: " << bot.evaluatePosition() << "\n"
            << "Bot's move: " << botsMove.toString() << "\n";

        bot.makeRealMove(botsMove);
      }


      Menu::printBoard(bot.realBoard);
    }
  }
} // namespace Program
