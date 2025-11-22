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

    bot.realBoard.setFromFEN("8/1p2bppk/4p2p/3pP3/1P1P4/5N1P/r5q1/1R2R1K1 w - - 0 30");

    Menu::init();

    Menu::printBoard(bot.realBoard);

    while (true)
    {
      auto moveStr = Menu::getMove();
      Move::Move move(moveStr.first, moveStr.second);
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
