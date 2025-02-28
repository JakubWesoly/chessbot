#include "Brain.hpp"
#include <iostream>
#include "Menu.hpp"

namespace Brain
{
  Brain::Brain()
  {
    this->neurons = readNeurons();
  }

  Brain::Brain(const std::string& FEN) {
    this->neurons = readNeurons();
    this->realBoard.setFromFEN(FEN);
    this->testBoard.setFromFEN(FEN);
  }

  bool Brain::makeRealMove(Move::Move move)
  {
    // auto moves = realBoard.getAllValidMoves();

    // std::cout << "size: " << moves.size() << std::endl;
    // for (auto &move : moves)
    // {
    //   std::cout << move.toString() << " " << move.to << std::endl;
    // }

    // this->testBoard.makeMove(move);
    bool success = this->realBoard.makeMove(move);

    if(success) {
      this->testBoard = this->realBoard;
    }

    return success;
  }

  bool Brain::makeTestMove(Move::Move move)
  {
    // auto moves = realBoard.getAllValidMoves();

    // std::cout << "size: " << moves.size() << std::endl;
    // for (auto &move : moves)
    // {
    //   std::cout << move.toString() << " " << move.to << std::endl;
    // }

    // this->testBoard.makeMove(move);
    return this->testBoard.makeMove(move);
  }

  double Brain::evaluatePosition()
  {
    double result = 0;

    for (auto &node : neurons)
    {
      result += evaluateNode(node);
    }

    return result;
  }

  Move::Move Brain::findBestMove()
  {
    // std::cout << "WG BOTA TURA: " << (this->testBoard.isWhiteTurn ? "BIALEGO" : "CZARNEGO") << "\n";
    auto moves = this->testBoard.getAllValidMoves();

    std::cout << "size: " << moves.size() << std::endl;
    for (auto &move : moves)
    {
      std::cout << move.toString() << " " << move.to << std::endl;
    }

    double bestScore = -1000000;
    Move::Move bestMove(true);

    for (auto &move : moves)
    {
      std::cout << "WG BOTA TURA: " << (this->testBoard.isWhiteTurn ? "BIALEGO" : "CZARNEGO") << "\n";

      // auto xd = this->testBoard.getAllValidMoves();

      std::cout <<"KRUWAAA: " << move.toString() << "\n";

    //   for (auto &move : xd)
    // {
    //   std::cout << move.toString() << " " << move.to << std::endl;
    // }

      auto v = this->testBoard.makeMove(move);
      // std::cout << "Valid? " << v << "\n";
      double score = evaluatePosition();
      this->testBoard.undoMove();
      
      
      // std::cout <<"BOARD PO TESCIE " << "\n";
      // Menu::printBoard(this->testBoard);
      
      // std::cout << "PO WSZYSTKIM WG BOTA TURA: " << (this->testBoard.isWhiteTurn ? "BIALEGO" : "CZARNEGO") << "\n\n\n\n";
    // std::cout << "TESTUJE RUCH: " << move.toString() << std::endl;

      if (score > bestScore)
      {
        bestScore = score;
        bestMove = move;
      }
    }

    return bestMove;
  }

  double Brain::evaluateNode(EvaluationNode node)
  {
    switch (node.type)
    {
    case EvaluationTypes::MATERIAL:
      return calculateMaterialDifference() * node.value;
    case EvaluationTypes::SPACE:
      return evaluateSpace() * node.value;
    case EvaluationTypes::KING_SAFETY:
      return evaluateKingSafety() * node.value;
    case EvaluationTypes::PIECE_ACTIVITY:
      return evaluatePieceActivity() * node.value;
    default:
      return 0;
    }
  }

  int Brain::calculateMaterialDifference()
  {
    int result = 0;

    for (int i = 0; i < 64; i++)
    {
      if (this->testBoard.board[i] == Board::Board::NONE)
        continue;

      if (this->testBoard.getPiece(i) == (Board::Board::PAWN | !isWhite))
        result += 1;
      else if (this->testBoard.getPiece(i) == (Board::Board::KNIGHT | !isWhite))
        result += 3;
      else if (this->testBoard.getPiece(i) == (Board::Board::BISHOP | !isWhite))
        result += 3;
      else if (this->testBoard.getPiece(i) == (Board::Board::ROOK | !isWhite))
        result += 5;
      else if (this->testBoard.getPiece(i) == (Board::Board::QUEEN | !isWhite))
        result += 9;
    }

    return result;
  }

  double Brain::evaluatePieceActivity()
  {
    double result = 0;

    // Space will be evaluated in the following manner:
    // 1. The more space a piece controls, the better
    // 2. The more space a piece controls, the better
    // 3. A square controlled in the enemy's half is double the value of the player's half
    // 4. A square controlled in the center is double the value of the player's half

    for (int i = 0; i < 64; i++)
    {
      if (this->testBoard.board[i] == Board::Board::NONE)
        continue;

      if (this->testBoard.getPiece(i) == (Board::Board::KNIGHT | !isWhite))
      {
        std::vector<int> knightPositions = {};

        for (int i = 0; i < 64; i++)
        {
          if (this->testBoard.getPiece(i) == (Board::Board::KNIGHT | !isWhite))
          {
            knightPositions.push_back(i);
          }
        }

        constexpr int knightOffsets[] = {Board::Board::UP + Board::Board::UP + Board::Board::LEFT,
                                         Board::Board::UP + Board::Board::UP + Board::Board::RIGHT,
                                         Board::Board::UP + Board::Board::LEFT + Board::Board::LEFT,
                                         Board::Board::UP + Board::Board::RIGHT + Board::Board::RIGHT,
                                         Board::Board::DOWN + Board::Board::DOWN + Board::Board::LEFT,
                                         Board::Board::DOWN + Board::Board::DOWN + Board::Board::RIGHT,
                                         Board::Board::DOWN + Board::Board::LEFT + Board::Board::LEFT,
                                         Board::Board::DOWN + Board::Board::RIGHT + Board::Board::RIGHT};

        for (auto &position : knightPositions)
        {
          for (auto &offset : knightOffsets)
          {
            if (Board::Board::checkIfFitsInBoard(position + offset))
            {
              if (this->testBoard.isOnEnemySide(position + offset, isWhite))
                result += 2;
              else
                result += 1;
            }
          }
        }
      }
      else if (this->testBoard.getPiece(i) == (Board::Board::BISHOP | !isWhite))
      {
        std::vector<int> bishopPositions = {};

        for (int i = 0; i < 64; i++)
        {
          if (this->testBoard.getPiece(i) == (Board::Board::BISHOP | !isWhite))
          {
            bishopPositions.push_back(i);
          }
        }

        std::vector<int> possibleSquares = {};

        for (auto &position : bishopPositions)
        {
          auto squares = this->testBoard.getDiagonalMoves(position);

          for (auto &square : squares)
          {
            possibleSquares.push_back(square.first);
          }
        }

        for (auto &square : possibleSquares)
        {
          if (this->testBoard.isOnEnemySide(square, isWhite))
            result += 2;
          else
            result += 1;
        }
      }
      else if (this->testBoard.getPiece(i) == (Board::Board::ROOK | !isWhite))
      {
        std::vector<int> rookPositions = {};

        for (int i = 0; i < 64; i++)
        {
          if (this->testBoard.getPiece(i) == (Board::Board::ROOK | !isWhite))
          {
            rookPositions.push_back(i);
          }
        }

        std::vector<int> possibleSquares = {};

        for (auto &position : rookPositions)
        {
          auto squares = this->testBoard.getVerticalAndHorizontalMoves(position);

          for (auto &square : squares)
          {
            possibleSquares.push_back(square.first);
          }
        }

        for (auto &square : possibleSquares)
        {
          if (this->testBoard.isOnEnemySide(square, isWhite))
            result += 2;
          else
            result += 1;
        }
      }
      else if (this->testBoard.getPiece(i) == (Board::Board::QUEEN | !isWhite))
      {
        std::vector<int> queenPositions = {};

        for (int i = 0; i < 64; i++)
        {
          if (this->testBoard.getPiece(i) == (Board::Board::QUEEN | !isWhite))
          {
            queenPositions.push_back(i);
          }
        }

        std::vector<int> possibleSquares = {};

        for (auto &position : queenPositions)
        {
          auto squares = this->testBoard.getVerticalAndHorizontalMoves(position);
          auto squares2 = this->testBoard.getDiagonalMoves(position);

          for (auto &square : squares)
          {
            possibleSquares.push_back(square.first);
          }
          for (auto &square : squares2)
          {
            possibleSquares.push_back(square.first);
          }
        }

        for (auto &square : possibleSquares)
        {
          if (this->testBoard.isOnEnemySide(square, isWhite))
            result += 2;
          else
            result += 1;
        }
      }
    }

    return result / optimalPieceActivity;
  }

  double Brain::evaluateSpace()
  {
    double result = 0;

    for (int i = 0; i < 64; i++)
    {
      if (this->testBoard.getPiece(i) == Board::Board::NONE)
        continue;

      if (this->testBoard.getPiece(i) == (Board::Board::PAWN | !isWhite))
      {
        result += i / 8;
      }
    }

    return result;
  }

  double Brain::evaluateKingSafety()
  {
    double result = 0;

    int kingPosition = this->testBoard.currentWhiteKingPosition;
    if (!isWhite)
      kingPosition = this->testBoard.currentBlackKingPosition;

    int pawnsInFront = 0;
    for (int i = 1; i <= 2; i++)
    {
      int currentlyCheckedPosition = kingPosition + Board::Board::UP * i;
      if (Board::Board::checkIfFitsInBoard(currentlyCheckedPosition) && this->testBoard.getPiece(currentlyCheckedPosition) == (Board::Board::PAWN | isWhite))
        pawnsInFront++;
      currentlyCheckedPosition = kingPosition + Board::Board::UP * i + Board::Board::LEFT;
      if (Board::Board::checkIfFitsInBoard(currentlyCheckedPosition) &&
          Board::Board::checkIfCrossesBorder(currentlyCheckedPosition, currentlyCheckedPosition - Board::Board::LEFT) &&
          this->testBoard.getPiece(currentlyCheckedPosition) == (Board::Board::PAWN | isWhite))
        pawnsInFront++;
      currentlyCheckedPosition = kingPosition + Board::Board::UP * i + Board::Board::RIGHT;
      if (Board::Board::checkIfFitsInBoard(currentlyCheckedPosition) &&
          Board::Board::checkIfCrossesBorder(currentlyCheckedPosition, currentlyCheckedPosition - Board::Board::RIGHT) &&
          this->testBoard.getPiece(currentlyCheckedPosition) == (Board::Board::PAWN | isWhite))
        pawnsInFront++;
    }

    int defenders = 0;

    for (int i = kingPosition + 14; i >= kingPosition - 18; i--)
    {
      if (!Board::Board::checkIfFitsInBoard(i) || this->testBoard.getPiece(i) <= (Board::Board::PAWN | Board::Board::COLOR))
        continue;

      // It is often said that a knight is king's best defender therefore the value is higher
      if (this->testBoard.getPiece(i) == (Board::Board::KNIGHT | isWhite))
        defenders += 5;
      else
      {
        // Remove the color bit
        defenders += (this->testBoard.getPiece(i) >> 1) << 1;
      }
    }

    int controledAdjacenedSquared = 0;

    for (int i = kingPosition + 8; i >= kingPosition - 9; i--)
    {
      if (!Board::Board::checkIfFitsInBoard(i))
        continue;

      if (this->testBoard.isSquareControled(i) != -1)
        controledAdjacenedSquared++;
    }

    const int centerSquare = isWhite ? 28 : 35;
    int howCloseToCenter = 0;

    int dx = abs(kingPosition % 8 - centerSquare % 8);
    int dy = abs(kingPosition / 8 - centerSquare / 8);

    // Avoiding using sqrt, dividing by 2 gives a rought estimate without the performance hit
    howCloseToCenter = (dx * dx + dy * dy) >> 1;

    result = pawnsInFront + defenders - controledAdjacenedSquared - howCloseToCenter;

    if (result < 0)
      return 0;

    return result / optimalKingSafety;
  }

  std::vector<EvaluationNode> Brain::readNeurons()
  {
    std::ifstream source(neuronsSource);

    std::vector<EvaluationNode> neurons;

    std::string line;
    

    while (std::getline(source, line)) 
    {
      std::string type = line.substr(0, line.find("="));
      std::string value = line.substr(line.find("=") + 1, line.length());

      EvaluationNode node;

      if (type == "MATERIAL")
      {
        node.type = EvaluationTypes::MATERIAL;
      }
      else if (type == "SPACE")
      {
        node.type = EvaluationTypes::SPACE;
      }
      else if (type == "KING_SAFETY")
      {
        node.type = EvaluationTypes::KING_SAFETY;
      }
      else if (type == "PIECE_ACTIVITY")
      {
        node.type = EvaluationTypes::PIECE_ACTIVITY;
      }

      node.value = std::stod(value);

      neurons.push_back(node);
    }

    return neurons;
  }
}