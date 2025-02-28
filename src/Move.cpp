#include "Move.hpp"

#include <algorithm>
#include <iostream>

namespace Move
{
  // Move::Move(PieceType pieceType, char from, char to[])
  // {
  //   this->pieceType = pieceType;
  //   this->from = from;
  //   this->to[0] = to[0];
  //   this->to[1] = to[1];
  // }

  Move::Move(const std::string &move)
  {
    // Check what type of piece is moving
    setPieceType(move);
    
    // Verifiaction Steps
    // 1. Check if the move is a castle move, because it doesn't need further verification
    if (checkAndSetCastle(move))
      return;

    // 2. There is no move, that is shorter than 2 characters
    if (move.size() < 2)
    {
      isValid = false;
      return;
    }

    // 3. If there is a capture, then add the capture move type
    if (std::find(move.begin(), move.end(), 'x') != move.end())
    {
      moveTypes.push_back(MoveTypes::CAPTURE);
    }

    // 4. If there is a promotion, then add the promotion move type 
    if (pieceType == PieceType::PAWN && std::find(move.begin(), move.end(), '=') != move.end())
    {
      moveTypes.push_back(MoveTypes::PROMOTION);
      char pawnPromotedTo = move.back();
      switch (pawnPromotedTo)
      {
      case 'N':
        promotionTo = PieceType::KNIGHT;
        break;
      case 'Q':
        promotionTo = PieceType::QUEEN;
        break;
      case 'B':
        promotionTo = PieceType::BISHOP;
        break;
      case 'R':
        promotionTo = PieceType::ROOK;
        break;
      default:
        promotionTo = PieceType::NONE; 
        isValid = false;
        break;
      }
    }

    // 5. Get where the piece is moving to
    // When there is a promotion, the last two characters are the piece that is being promoted to
    if (pieceType == PieceType::PAWN && std::find(moveTypes.begin(), moveTypes.end(), MoveTypes::PROMOTION) != moveTypes.end())
    {
      if (move.size() < 4)
      {
        isValid = false;
        return;
      }
      to = getSquareIndex(move.substr(move.size() - 4, 2));
    }
    // When there is no promotion, the last two characters are the piece that is being moved to
    else
    {
      to = getSquareIndex(move.substr(move.size() - 2, 2));
    }
  }

  Move::Move(int from, int to, PieceType pieceType, std::vector<MoveTypes> moveTypes)
  {
    this->from = from;
    this->to = to;
    this->pieceType = pieceType;
    this->moveTypes = moveTypes;
  }

  Move::Move(int from, int to, PieceType pieceType, std::vector<MoveTypes> moveTypes, PieceType promotionTo)
  {
    this->from = from;
    this->to = to;
    this->pieceType = pieceType;
    this->moveTypes = moveTypes;
    this->promotionTo = promotionTo;
  }

  Move::Move(bool isValid)
  {
    this->isValid = isValid;
  }

  void Move::setPieceType(const std::string &move)
  {
    if (move.empty())
    {
      throw std::invalid_argument("Move is empty");
      return;
    }
    switch (move[0])
    {
    case 'N':
      pieceType = PieceType::KNIGHT;
      break;

    case 'Q':
      pieceType = PieceType::QUEEN;
      break;

    case 'B':
      pieceType = PieceType::BISHOP;
      break;

    case 'R':
      pieceType = PieceType::ROOK;
      break;

    case 'K':
      pieceType = PieceType::KING;
      break;

    default:
      if (move[0] >= 'a' && move[0] <= 'h')
      {
        pieceType = PieceType::PAWN;
      }
      else
      {
        pieceType = PieceType::NONE;
      }
      break;
    }
  }

  bool Move::checkAndSetCastle(const std::string &move)
  {
    if (move.empty())
    {
      return false;
    }
    if (move == "O-O")
    {
      moveTypes.push_back(MoveTypes::SHORT_CASTLE);
      pieceType = PieceType::KING;
      return true;
    }
    else if (move == "O-O-O")
    {
      moveTypes.push_back(MoveTypes::LONG_CASTLE);
      pieceType = PieceType::KING;
      return true;
    }
    return false;
  }

  int Move::getSquareIndex(const std::string &move)
  {
    if (move.empty())
    {
      throw std::invalid_argument("Move is empty");
    }

    if (move.size() != 2) 
    {
    throw std::invalid_argument("Invalid square format: " + move);
    }

    if (move[0] < 'a' || move[0] > 'h' || move[1] < '1' || move[1] > '8') {
    throw std::invalid_argument("Invalid chess square: " + move);
    }

    // Convert the move to a square index
    return (move[1] - '1') * 8 + (move[0] - 'a');
  }

  std::string Move::toString() const
  {
    std::string move = "";

    bool isCapture = std::find(moveTypes.begin(), moveTypes.end(), MoveTypes::CAPTURE) != moveTypes.end();
    bool isPromotion = std::find(moveTypes.begin(), moveTypes.end(), MoveTypes::PROMOTION) != moveTypes.end();
    bool isShortCastle = std::find(moveTypes.begin(), moveTypes.end(), MoveTypes::SHORT_CASTLE) != moveTypes.end();
    bool isLongCastle = std::find(moveTypes.begin(), moveTypes.end(), MoveTypes::LONG_CASTLE) != moveTypes.end();

    // If the move is a castle move, return the castle move
    if (isShortCastle)
      return "O-O";
    else if (isLongCastle)
        return "O-O-O";


    // Add the piece type to the move
    switch (pieceType)
    {
    case PieceType::KNIGHT:
      move += "N";
      break;
    case PieceType::BISHOP:
      move += "B";
      break;
    case PieceType::ROOK:
      move += "R";
      break;
    case PieceType::QUEEN:
      move += "Q";
      break;
    case PieceType::KING:
      move += "K";
      break;
    default:
      break;
    }

    // Add the capture move type
    if (isCapture)
    {
      if (pieceType == PieceType::PAWN)
      {
        move += static_cast<char>(from % 8 + 'a');
      }

      move += "x";
    }

    // Add the square that the piece is moving to
    if (to != -1)
    {
      // int fromCopy = from;
      move += static_cast<char>(to % 8 + 'a');
      move += static_cast<char>(to / 8 + '1');
    }

    if (isPromotion)
    {
      switch (promotionTo)
      {
      case PieceType::KNIGHT:
        move += "=N";
        break;
      case PieceType::QUEEN:
        move += "=Q";
        break;
      case PieceType::BISHOP:
        move += "=B";
        break;
      case PieceType::ROOK:
        move += "=R";
        break;
      default:
        break;
      }
    }

    return move;
  }
}