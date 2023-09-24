#ifndef BRAIN_HPP
#define BRAIN_HPP

#include <string>
#include <fstream>

#include "Board.hpp"
#include "Move.hpp"

namespace Brain
{
  enum class EvaluationTypes
  {
    MATERIAL = 1,
    SPACE,
    KING_SAFETY,
    PIECE_ACTIVITY,
  };

  struct EvaluationNode
  {
    EvaluationTypes type;
    double value;
  };

  class Brain
  {
  public:
    Brain();
    ~Brain() = default;

    double evaluatePosition();
    Move::Move findBestMove();
    bool makeMove(Move::Move move);

    Board::Board realBoard;
    Board::Board testBoard;
    bool isWhite = false;

  private:
    std::vector<EvaluationNode> readNeurons();
    double evaluateNode(EvaluationNode node);
    double evaluateSpace();
    double evaluateKingSafety();
    double evaluatePieceActivity();
    int calculateMaterialDifference();

    constexpr static double optimalPieceActivity = 71.0;
    constexpr static double optimalSpace = 24.0;
    constexpr static double optimalKingSafety = 12.0;

    std::vector<EvaluationNode> neurons;
    std::string neuronsSource = "neurons.txt";
  };
} // namespace Brain

#endif // BRAIN_HPP
