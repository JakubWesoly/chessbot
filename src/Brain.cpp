#include "Brain.hpp"
#include <iostream>

namespace Brain
{

  bool Brain::makeMove(Move::Move move)
  {
    // this->testBoard.makeMove(move);
    auto moves = realBoard.getAllValidMoves();

    std::cout << "size: " << moves.size() << std::endl;
    for (auto &move : moves)
    {
      std::cout << move.toString() << std::endl;
    }

    return this->realBoard.makeMove(move);
  }
}