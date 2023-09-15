#ifndef BRAIN_HPP
#define BRAIN_HPP

#include <string>

#include "Board.hpp"
#include "Move.hpp"

namespace Brain
{
  class Brain
  {
  public:
    Brain() = default;
    ~Brain() = default;

    double evaluatePosition();
    Move::Move findBestMove();
    bool makeMove(Move::Move move);

    Board::Board realBoard;
    Board::Board testBoard;
    bool color = 0;
  };
} // namespace Brain

#endif // BRAIN_HPP
