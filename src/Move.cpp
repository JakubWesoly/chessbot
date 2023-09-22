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
    setPieceType(move);
    check_and_set_castle(move);

    if (std::find(moveTypes.begin(), moveTypes.end(), MoveTypes::SHORT_CASTLE) != moveTypes.end() ||
        std::find(moveTypes.begin(), moveTypes.end(), MoveTypes::LONG_CASTLE) != moveTypes.end())
    {
      return;
    }

    if (move.size() < 2)
    {
      isVaild = false;
      return;
    }

    if (std::find(move.begin(), move.end(), 'x') != move.end())
    {
      moveTypes.push_back(MoveTypes::CAPTURE);
    }

    if (pieceType == PieceType::PAWN && std::find(move.begin(), move.end(), '=') != move.end())
    {
      moveTypes.push_back(MoveTypes::PROMOTION);
      auto pawnPromotedTo = move.substr(move.size() - 1, 1);
      switch (pawnPromotedTo[0])
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
        break;
      }
    }

    if (pieceType == PieceType::PAWN && std::find(moveTypes.begin(), moveTypes.end(), MoveTypes::PROMOTION) != moveTypes.end())
    {
      to = getSquareIndex(move.substr(move.size() - 4, 2));
    }
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
    this->isVaild = isValid;
  }

  void Move::setPieceType(const std::string &move)
  {
    if (sizeof(move) == 0)
    {
      pieceType = PieceType::NONE;
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
      pieceType = PieceType::PAWN;
      break;
    }
  }

  void Move::check_and_set_castle(const std::string &move)
  {
    if (sizeof(move) == 0)
    {
      // throw an error
      return;
    }
    if (move == "O-O")
    {
      moveTypes.push_back(MoveTypes::SHORT_CASTLE);
      pieceType = PieceType::KING;
    }
    else if (move == "O-O-O")
    {
      moveTypes.push_back(MoveTypes::LONG_CASTLE);
      pieceType = PieceType::KING;
    }
  }

  int Move::getSquareIndex(const std::string &move)
  {
    if (sizeof(move) == 0)
    {
      // throw an error
      return -1;
    }
    return move[0] - 'a' + 8 * (move[1] - '1');
  }

  std::string Move::toString() const
  {
    std::string move = "";
    switch (pieceType)
    {
    case PieceType::PAWN:
      break;
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
      if (std::find(moveTypes.begin(), moveTypes.end(), MoveTypes::SHORT_CASTLE) != moveTypes.end())
        return "O-O";
      else if (std::find(moveTypes.begin(), moveTypes.end(), MoveTypes::LONG_CASTLE) != moveTypes.end())
        return "O-O-O";
      else
        move += "K";
      break;
    default:
      break;
    }

    if (std::find(moveTypes.begin(), moveTypes.end(), MoveTypes::CAPTURE) != moveTypes.end())
    {
      if (pieceType == PieceType::PAWN)
        move += from % 8 + 'a';
      move += "x";
    }

    if (to != -1)
    {
      // int fromCopy = from;
      move += static_cast<char>(to % 8 + 'a');
      move += to / 8 + '1';
    }

    if (std::find(moveTypes.begin(), moveTypes.end(), MoveTypes::PROMOTION) != moveTypes.end())
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