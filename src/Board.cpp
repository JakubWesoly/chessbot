#include "Board.hpp"

#include <algorithm>
#include <iostream>

namespace Board
{
  Board::Board()
  {
    setToDefault();
  }

  void Board::setToDefault()
  {
    int pieceSet[] = {Board::ROOK, Board::KNIGHT, Board::BISHOP, Board::QUEEN, Board::KING, Board::BISHOP, Board::KNIGHT, Board::ROOK};

    for (int i = 0; i < 8; i++)
    {
      board[i] = pieceSet[i];
      board[i + 56] = Board::COLOR | pieceSet[i];
    }

    for (int i = 8; i < 16; i++)
    {
      board[i] = Board::PAWN;
      board[i + 40] = Board::COLOR | Board::PAWN;
    }

    currentWhiteKingPosition = 4;
    currentBlackKingPosition = 60;
  }

  bool Board::makeMove(const Move::Move &move)
  {
    Move::Move chechedMove = isValidMove(move);
    if (!chechedMove.isVaild)
      return false;
    bool isValidMove;
    if (std::find(chechedMove.moveTypes.begin(), chechedMove.moveTypes.end(), Move::MoveTypes::SHORT_CASTLE) != chechedMove.moveTypes.end())
    {
      return makeShortCastle();
    }
    else if (std::find(chechedMove.moveTypes.begin(), chechedMove.moveTypes.end(), Move::MoveTypes::LONG_CASTLE) != chechedMove.moveTypes.end())
    {
      return makeLongCastle();
    }
    else
    {
      isValidMove = makeRegularMove(chechedMove);
    }
    if (!isValidMove)
      return false;
    moveHistory.push_back(chechedMove);
    isWhiteTurn = !isWhiteTurn;
    return true;
  }

  std::vector<Move::Move> Board::getAllValidMoves()
  {
    std::vector<Move::Move> moves = {};
    std::vector<Move::Move> pawnMoves = getAllPawnMoves();
    std::vector<Move::Move> knightMoves = getAllKnightMoves();
    std::vector<Move::Move> bishopMoves = getAllBishopMoves();
    std::vector<Move::Move> rookMoves = getAllRookMoves();
    // std::vector<Move::Move> queenMoves = getAllQueenMoves();
    // std::vector<Move::Move> kingMoves = getAllKingMoves();

    moves.insert(moves.end(), pawnMoves.begin(), pawnMoves.end());
    moves.insert(moves.end(), knightMoves.begin(), knightMoves.end());
    moves.insert(moves.end(), bishopMoves.begin(), bishopMoves.end());
    moves.insert(moves.end(), rookMoves.begin(), rookMoves.end());
    // moves.insert(moves.end(), queenMoves.begin(), queenMoves.end());
    // moves.insert(moves.end(), kingMoves.begin(), kingMoves.end());

    return moves;
  }

  std::vector<Move::Move> Board::getAllPawnMoves()
  {
    std::vector<Move::Move> moves = {};

    for (int i = 0; i < 64; i++)
    {
      if (isWhiteTurn)
      {
        if (board[i] == Board::PAWN)
        {
          Move::Move movesList[] = {
              Move::Move(i, i + 8, Move::PieceType::PAWN, {}),
              Move::Move(i, i + 16, Move::PieceType::PAWN, {}),
              Move::Move(i, i + 7, Move::PieceType::PAWN, {Move::MoveTypes::CAPTURE}),
              Move::Move(i, i + 9, Move::PieceType::PAWN, {Move::MoveTypes::CAPTURE}),
              Move::Move(i, i + 8, Move::PieceType::PAWN, {Move::MoveTypes::PROMOTION}, Move::PieceType::QUEEN),
              Move::Move(i, i + 8, Move::PieceType::PAWN, {Move::MoveTypes::PROMOTION}, Move::PieceType::KNIGHT),
              Move::Move(i, i + 8, Move::PieceType::PAWN, {Move::MoveTypes::PROMOTION}, Move::PieceType::BISHOP),
              Move::Move(i, i + 8, Move::PieceType::PAWN, {Move::MoveTypes::PROMOTION}, Move::PieceType::ROOK),
              Move::Move(i, i + 7, Move::PieceType::PAWN, {Move::MoveTypes::CAPTURE, Move::MoveTypes::PROMOTION}, Move::PieceType::QUEEN),
              Move::Move(i, i + 7, Move::PieceType::PAWN, {Move::MoveTypes::CAPTURE, Move::MoveTypes::PROMOTION}, Move::PieceType::KNIGHT),
              Move::Move(i, i + 7, Move::PieceType::PAWN, {Move::MoveTypes::CAPTURE, Move::MoveTypes::PROMOTION}, Move::PieceType::BISHOP),
              Move::Move(i, i + 7, Move::PieceType::PAWN, {Move::MoveTypes::CAPTURE, Move::MoveTypes::PROMOTION}, Move::PieceType::ROOK),
              Move::Move(i, i + 9, Move::PieceType::PAWN, {Move::MoveTypes::CAPTURE, Move::MoveTypes::PROMOTION}, Move::PieceType::QUEEN),
              Move::Move(i, i + 9, Move::PieceType::PAWN, {Move::MoveTypes::CAPTURE, Move::MoveTypes::PROMOTION}, Move::PieceType::KNIGHT),
              Move::Move(i, i + 9, Move::PieceType::PAWN, {Move::MoveTypes::CAPTURE, Move::MoveTypes::PROMOTION}, Move::PieceType::BISHOP),
              Move::Move(i, i + 9, Move::PieceType::PAWN, {Move::MoveTypes::CAPTURE, Move::MoveTypes::PROMOTION}, Move::PieceType::ROOK),
          };

          for (const auto &move : movesList)
          {
            Move::Move checkedMove = isValidMove(move);
            if (checkedMove.isVaild)
            {
              moves.push_back(checkedMove);
            }
          }
        }
      }
      else
      {
        if (board[i] == (Board::PAWN | Board::COLOR))
        {
          Move::Move movesList[] = {
              Move::Move(i, i - 8, Move::PieceType::PAWN, {}),
              Move::Move(i, i - 16, Move::PieceType::PAWN, {}),
              Move::Move(i, i - 7, Move::PieceType::PAWN, {Move::MoveTypes::CAPTURE}),
              Move::Move(i, i - 9, Move::PieceType::PAWN, {Move::MoveTypes::CAPTURE}),
              Move::Move(i, i - 8, Move::PieceType::PAWN, {Move::MoveTypes::PROMOTION}, Move::PieceType::QUEEN),
              Move::Move(i, i - 8, Move::PieceType::PAWN, {Move::MoveTypes::PROMOTION}, Move::PieceType::KNIGHT),
              Move::Move(i, i - 8, Move::PieceType::PAWN, {Move::MoveTypes::PROMOTION}, Move::PieceType::BISHOP),
              Move::Move(i, i - 8, Move::PieceType::PAWN, {Move::MoveTypes::PROMOTION}, Move::PieceType::ROOK),
              Move::Move(i, i - 7, Move::PieceType::PAWN, {Move::MoveTypes::CAPTURE, Move::MoveTypes::PROMOTION}, Move::PieceType::QUEEN),
              Move::Move(i, i - 7, Move::PieceType::PAWN, {Move::MoveTypes::CAPTURE, Move::MoveTypes::PROMOTION}, Move::PieceType::KNIGHT),
              Move::Move(i, i - 7, Move::PieceType::PAWN, {Move::MoveTypes::CAPTURE, Move::MoveTypes::PROMOTION}, Move::PieceType::BISHOP),
              Move::Move(i, i - 7, Move::PieceType::PAWN, {Move::MoveTypes::CAPTURE, Move::MoveTypes::PROMOTION}, Move::PieceType::ROOK),
              Move::Move(i, i - 9, Move::PieceType::PAWN, {Move::MoveTypes::CAPTURE, Move::MoveTypes::PROMOTION}, Move::PieceType::QUEEN),
              Move::Move(i, i - 9, Move::PieceType::PAWN, {Move::MoveTypes::CAPTURE, Move::MoveTypes::PROMOTION}, Move::PieceType::KNIGHT),
              Move::Move(i, i - 9, Move::PieceType::PAWN, {Move::MoveTypes::CAPTURE, Move::MoveTypes::PROMOTION}, Move::PieceType::BISHOP),
              Move::Move(i, i - 9, Move::PieceType::PAWN, {Move::MoveTypes::CAPTURE, Move::MoveTypes::PROMOTION}, Move::PieceType::ROOK),
          };

          for (const auto &move : movesList)
          {
            Move::Move checkedMove = isValidMove(move);
            if (checkedMove.isVaild)
            {
              moves.push_back(checkedMove);
            }
          }
        }
      }
    }

    return moves;
  }

  std::vector<Move::Move> Board::getAllKnightMoves()
  {
    std::vector<Move::Move> moves;
    for (int i = 0; i < 64; i++)
    {
      if (isWhiteTurn)
      {
        if (board[i] == (Board::KNIGHT))
        {
          Move::Move movesList[] = {
              Move::Move(i, i + 17, Move::PieceType::KNIGHT, {}),
              Move::Move(i, i + 15, Move::PieceType::KNIGHT, {}),
              Move::Move(i, i + 10, Move::PieceType::KNIGHT, {}),
              Move::Move(i, i + 6, Move::PieceType::KNIGHT, {}),
              Move::Move(i, i - 17, Move::PieceType::KNIGHT, {}),
              Move::Move(i, i - 15, Move::PieceType::KNIGHT, {}),
              Move::Move(i, i - 10, Move::PieceType::KNIGHT, {}),
              Move::Move(i, i - 6, Move::PieceType::KNIGHT, {}),
          };
          for (const auto &move : movesList)
          {
            Move::Move checkedMove = isValidMove(move);
            if (checkedMove.isVaild)
            {
              // std::cout << checkedMove.toString() << std::endl;
              moves.push_back(checkedMove);
            }
          }
        }
      }
      else
      {
        if (board[i] == (Board::KNIGHT | Board::COLOR))
        {
          Move::Move movesList[] = {
              Move::Move(i, i + 17, Move::PieceType::KNIGHT, {}),
              Move::Move(i, i + 15, Move::PieceType::KNIGHT, {}),
              Move::Move(i, i + 10, Move::PieceType::KNIGHT, {}),
              Move::Move(i, i + 6, Move::PieceType::KNIGHT, {}),
              Move::Move(i, i - 17, Move::PieceType::KNIGHT, {}),
              Move::Move(i, i - 15, Move::PieceType::KNIGHT, {}),
              Move::Move(i, i - 10, Move::PieceType::KNIGHT, {}),
              Move::Move(i, i - 6, Move::PieceType::KNIGHT, {})};
          for (const auto &move : movesList)
          {
            Move::Move checkedMove = isValidMove(move);
            if (checkedMove.isVaild)
            {
              moves.push_back(checkedMove);
            }
          }
        }
      }
    }
    return moves;
  }

  std::vector<Move::Move> Board::getAllBishopMoves()
  {
    std::vector<Move::Move> moves;
    for (int i = 0; i < 64; i++)
    {
      if (board[i] == (Board::BISHOP | !isWhiteTurn))
      {
        std::vector<std::pair<int, bool>> fromList = getDiagonalMoves(i);
        for (auto [to, isCapture] : fromList)
        {
          // std::cout << "from: " << from << " | to: " << i << " | isCapture: " << isCapture << std::endl;
          moves.push_back(Move::Move(i, to, Move::PieceType::BISHOP, (isCapture ? std::vector<Move::MoveTypes>{Move::MoveTypes::CAPTURE} : std::vector<Move::MoveTypes>{})));
        }
      }
    }
    return moves;
  }

  std::vector<Move::Move> Board::getAllRookMoves()
  {
    std::vector<Move::Move> moves;
    for (int i = 0; i < 64; i++)
    {
      if (board[i] == (Board::ROOK | !isWhiteTurn))
      {
        std::vector<std::pair<int, bool>> fromList = getVerticalAndHorizontalMoves(i);
        for (auto [to, isCapture] : fromList)
        {
          // std::cout << "from: " << from << " | to: " << i << " | isCapture: " << isCapture << std::endl;
          moves.push_back(Move::Move(i, to, Move::PieceType::ROOK, (isCapture ? std::vector<Move::MoveTypes>{Move::MoveTypes::CAPTURE} : std::vector<Move::MoveTypes>{})));
        }
      }
    }
    return moves;
  }

  Move::Move Board::checkIfAmbiguous(const std::vector<Move::Move> &checkedMoves)
  {
    switch (checkedMoves.size())
    {
    case 0:
      return Move::Move(false);
    case 1:
      return checkedMoves[0];
    default:
      std::cout << "Ambiguous move" << std::endl;
      return Move::Move(false);
    }
  }

  Move::Move Board::isValidMove(const Move::Move &move)
  {
    std::vector<Move::Move> checkedMoves;
    switch (move.pieceType)
    {
    case Move::PieceType::PAWN:
      return checkIfAmbiguous(getValidPawnMoves(move));
    case Move::PieceType::KNIGHT:
      return checkIfAmbiguous(getValidKnightMoves(move));
    case Move::PieceType::BISHOP:
      return checkIfAmbiguous(getValidBishopMoves(move));
    case Move::PieceType::ROOK:
      return checkIfAmbiguous(getValidRookMoves(move));
    case Move::PieceType::QUEEN:
      return checkIfAmbiguous(getValidQueenMoves(move));
    case Move::PieceType::KING:
      return checkIfAmbiguous(getValidKingMoves(move));
    default:
      return Move::Move(false);
    }
  }

  std::vector<Move::Move> Board::getValidPawnMoves(const Move::Move &move)
  {
    int targetSquare = move.to;

    auto [isPromotionMoveViable, promotionMove] = checkForPromotion(move);

    if (isPromotionMoveViable)
    {
      return {promotionMove};
    }

    auto [isEnPassantViable, enPassant] = checkForEnPassant(move);

    if (isEnPassantViable)
    {
      return {enPassant};
    }

    // Check if the move is a capture
    if (std::find(move.moveTypes.begin(), move.moveTypes.end(), Move::MoveTypes::CAPTURE) != move.moveTypes.end())
    {
      if (board[targetSquare] == Board::NONE)
        return {};

      if (isWhiteTurn)
      {
        // Check if the target square is a white piece or empty
        if (!(board[targetSquare] & Board::COLOR))
          return {};

        // Check if the squares from the capture is possible are occupied with white pawns
        if (((targetSquare >= 7 && board[targetSquare + Board::DOWN_RIGHT] != Board::PAWN) && (targetSquare >= 9 && board[targetSquare + Board::DOWN_LEFT] != Board::PAWN)))
          return {};

        if (targetSquare >= 7 && board[targetSquare + Board::DOWN_RIGHT] == Board::PAWN && !isOnRightBorder(targetSquare))
        {
          return {Move::Move(targetSquare + Board::DOWN_RIGHT, targetSquare, Move::PieceType::PAWN, {Move::MoveTypes::CAPTURE})};
        }
        else if (targetSquare >= 9 && board[targetSquare + Board::DOWN_LEFT] == Board::PAWN && !isOnLeftBorder(targetSquare))
        {
          return {Move::Move(targetSquare + Board::DOWN_LEFT, targetSquare, Move::PieceType::PAWN, {Move::MoveTypes::CAPTURE})};
        }
      }
      else
      {
        // Check if the target square is a black piece or empty
        if ((board[targetSquare] & Board::COLOR))
          return {};

        // Check if the squares from the capture is possible are occupied with black pawns
        if (((targetSquare <= 56 && board[targetSquare + Board::UP_LEFT] != (Board::COLOR | Board::PAWN)) && (targetSquare <= 54 && board[targetSquare + Board::UP_RIGHT] != (Board::COLOR | Board::PAWN))))
          return {};

        if (targetSquare <= 56 && board[targetSquare + Board::UP_LEFT] == (Board::COLOR | Board::PAWN) && !isOnLeftBorder(targetSquare))
        {
          return {Move::Move(targetSquare + Board::UP_LEFT, targetSquare, Move::PieceType::PAWN, {Move::MoveTypes::CAPTURE})};
        }
        else if (targetSquare <= 54 && board[targetSquare + Board::UP_RIGHT] == (Board::COLOR | Board::PAWN) && !isOnRightBorder(targetSquare))
        {
          return {Move::Move(targetSquare + Board::UP_RIGHT, targetSquare, Move::PieceType::PAWN, {Move::MoveTypes::CAPTURE})};
        }
      }
    }
    else
    {
      // A normal move
      // Check if the target square is empty
      if (board[targetSquare] != Board::NONE)
        return {};

      if (isWhiteTurn)
      {
        // Check for a move two squares forward
        if (targetSquare >= 24 && targetSquare <= 31)
        {
          // std::cout << targetSquare - 16 << std::endl;
          if (board[targetSquare + Board::DOWN] == Board::PAWN)
          {
            return {Move::Move(targetSquare + Board::DOWN, targetSquare, Move::PieceType::PAWN, {})};
          }
          else if ((board[targetSquare + (Board::DOWN * 2)] == Board::PAWN && board[targetSquare + (Board::DOWN)] == Board::NONE))
          {
            return {Move::Move(targetSquare + (Board::DOWN * 2), targetSquare, Move::PieceType::PAWN, {})};
          }
        }
        else
        {
          if (board[targetSquare + Board::DOWN] == Board::PAWN)
          {
            return {Move::Move(targetSquare + Board::DOWN, targetSquare, Move::PieceType::PAWN, {})};
          }
        }
      }
      else
      {
        // Check for a move two squares forward
        if (targetSquare >= 32 && targetSquare <= 39)
        {
          if (board[targetSquare + Board::UP] == 3)
          {
            return {Move::Move(targetSquare + Board::UP, targetSquare, Move::PieceType::PAWN, {})};
          }
          else if ((board[targetSquare + (Board::UP * 2)] == 3 && board[targetSquare + Board::UP] == 0))
          {
            return {Move::Move(targetSquare + (Board::UP * 2), targetSquare, Move::PieceType::PAWN, {})};
          }
        }
        else
        {
          if (board[targetSquare + Board::UP] == 3)
            return {Move::Move(targetSquare + Board::UP, targetSquare, Move::PieceType::PAWN, {})};
        }
      }
    }

    return {};
  }

  std::vector<Move::Move> Board::getValidKnightMoves(const Move::Move &move)
  {
    std::vector<int> fromList = {};
    std::vector<Move::Move> result = {};
    if (move.from == -1)
    {
      fromList = checkKnightMoves(move.to);
      if (fromList.size() == 0)
      {
        return {};
      }
    }
    else
    {
      fromList.push_back(move.from);
    }
    for (const int &from : fromList)
    {
      std::vector<Move::MoveTypes> appendedMoveTypes;

      if (board[move.to] != Board::NONE)
      {
        if (isWhiteTurn)
        {
          if (!(board[move.to] & Board::COLOR))
            continue;
          else
            appendedMoveTypes.push_back(Move::MoveTypes::CAPTURE);
        }
        else
        {
          if ((board[move.to] & Board::COLOR))
            continue;
          else
            appendedMoveTypes.push_back(Move::MoveTypes::CAPTURE);
        }
      }

      if (from + move.to < 0 || move.to < 0 || move.to >= 64 || from < 0 || from >= 64)
      {
        continue;
      }
      // Check if knight jump doesnt jump over the boards bounds, making him move to the other side of the board
      if (abs(from % 8 - move.to % 8) > 2 || abs(from / 8 - move.to / 8) > 2)
      {
        // std::cout << "out of bounds | from: " << from << " | to: " << move.to << " | result: " << abs(from % 8 - move.to % 8) << std::endl;
        continue;
      }
      if (isWhiteTurn)
      {
        if (board[from] != Board::KNIGHT)
          continue;
      }
      else
      {
        if (board[from] != (Board::KNIGHT | Board::COLOR))
          continue;
      }
      result.push_back(Move::Move(from, move.to, Move::PieceType::KNIGHT, appendedMoveTypes));
    }
    return result;
  }

  std::vector<Move::Move> Board::getValidBishopMoves(const Move::Move &move)
  {
    std::vector<Move::Move> result = {};

    bool isCapture = std::find(move.moveTypes.begin(), move.moveTypes.end(), Move::MoveTypes::CAPTURE) != move.moveTypes.end();

    int from = checkDiagonal(move.to, Move::PieceType::BISHOP, isCapture);

    if (from == -1)
    {
      return {};
    }

    if (isCapture)
    {
      if (isWhiteTurn)
      {
        if (!(board[move.to] & 1))
          return {};
      }
      else
      {
        if ((!board[move.to] && board[move.to] & 0))
          return {};
      }
    }
    else
    {
      if (board[move.to] != 0)
        return {};
    }

    if (isWhiteTurn)
    {
      if (board[from] != 8)
        return {};
    }
    else
    {
      if (board[from] != 9)
        return {};
    }

    return {Move::Move(from, move.to, Move::PieceType::BISHOP, {})};
  }

  std::vector<Move::Move> Board::getValidRookMoves(const Move::Move &move)
  {
    std::vector<Move::Move> result = {};
    bool isCapture = std::find(move.moveTypes.begin(), move.moveTypes.end(), Move::MoveTypes::CAPTURE) != move.moveTypes.end();
    std::vector<int> fromList = {};

    if (move.from == -1)
    {
      fromList = checkVerticalAndHorizontal(move.to, Move::PieceType::ROOK, isCapture);

      if (fromList.size() == 0)
      {
        return {};
      }
    }
    else
    {
      fromList.push_back(move.from);
    }

    for (const int &from : fromList)
    {
      if (isCapture)
      {
        if (board[move.to] == Board::NONE)
          continue;

        if (isWhiteTurn && !(board[move.to] & Board::COLOR))
          continue;
        else if (!isWhiteTurn && (board[move.to] & Board::COLOR))
          continue;

        result.push_back(Move::Move(from, move.to, Move::PieceType::ROOK, {Move::MoveTypes::CAPTURE}));
        continue;
      }
      else
      {
        if (board[move.to] != Board::NONE)
          continue;
      }

      if (isWhiteTurn)
      {
        if (board[from] != Board::ROOK)
          continue;
      }
      else
      {
        if (board[from] != (Board::ROOK | Board::COLOR))
          continue;
      }

      result.push_back(Move::Move(from, move.to, Move::PieceType::ROOK, {}));
    }

    // if (isCapture)
    // {
    //   if (isWhiteTurn)
    //   {
    //     if (!(board[move.to] & 1))
    //       return {};
    //   }
    //   else
    //   {
    //     if ((!board[move.to] && board[move.to] & 0))
    //       return {};
    //   }
    // }
    // else
    // {
    //   if (board[move.to] != 0)
    //     return {};
    // }

    // if (isWhiteTurn)
    // {
    //   if (board[from] != 16)
    //     return {};
    // }
    // else
    // {
    //   if (board[from] != 17)
    //     return {};
    // }

    // return {Move::Move(from, move.to, Move::PieceType::ROOK, {})};

    return result;
  }

  std::vector<Move::Move> Board::getValidQueenMoves(const Move::Move &move)
  {
    bool isCapture = std::find(move.moveTypes.begin(), move.moveTypes.end(), Move::MoveTypes::CAPTURE) != move.moveTypes.end();

    // int from = checkVerticalAndHorizontal(move.to, Move::PieceType::QUEEN, isCapture);
    int from = 0;
    // if (from == -1)
    // {
    //   from = checkDiagonal(move.to, Move::PieceType::QUEEN, isCapture);
    // }

    if (from == -1)
    {
      return {};
    }

    if (isCapture)
    {
      if (isWhiteTurn)
      {
        if (!(board[move.to] & 1))
          return {};
      }
      else
      {
        if ((!board[move.to] && board[move.to] & 0))
          return {};
      }
    }
    else
    {
      if (board[move.to] != 0)
        return {};
    }

    if (isWhiteTurn)
    {
      if (board[from] != 32)
        return {};
    }
    else
    {
      if (board[from] != 33)
        return {};
    }

    return {Move::Move(from, move.to, Move::PieceType::QUEEN, {})};
  }

  std::vector<Move::Move> Board::getValidKingMoves(const Move::Move &move)
  {
    if (std::find(move.moveTypes.begin(), move.moveTypes.end(), Move::MoveTypes::SHORT_CASTLE) != move.moveTypes.end())
    {
      if (isWhiteTurn)
      {
        if (hasWhiteKingMoved || hasWhiteRookHMoved)
        {
          return {};
        }
        if (board[5] != 0 || board[6] != 0)
        {
          return {};
        }
        if (isSquareControled(5) != -1 || isSquareControled(6) != -1)
        {
          // std::cout << isSquareControled(5) << " ||| " << isSquareControled(6) << std::endl;
          return {};
        }
        return {Move::Move(60, 62, Move::PieceType::KING, {Move::MoveTypes::SHORT_CASTLE})};
      }
      else
      {
        if (hasBlackKingMoved || hasBlackRookHMoved)
        {
          return {};
        }
        if (board[61] != 0 || board[62] != 0)
        {
          return {};
        }
        if (isSquareControled(61) != -1 || isSquareControled(62) != -1)
        {
          return {};
        }
        return {Move::Move(4, 6, Move::PieceType::KING, {Move::MoveTypes::SHORT_CASTLE})};
      }
    }

    if (std::find(move.moveTypes.begin(), move.moveTypes.end(), Move::MoveTypes::LONG_CASTLE) != move.moveTypes.end())
    {
      if (isWhiteTurn)
      {
        if (hasWhiteKingMoved || hasWhiteRookAMoved)
        {
          return {};
        }
        if (board[3] != 0 || board[2] != 0 || board[1] != 0)
        {
          return {};
        }
        if (isSquareControled(3) != -1 || isSquareControled(2) != -1)
        {
          return {};
        }
        return {Move::Move(60, 58, Move::PieceType::KING, {Move::MoveTypes::LONG_CASTLE})};
      }
      else
      {
        if (hasBlackKingMoved || hasBlackRookAMoved)
        {
          return {};
        }
        if (board[59] != 0 || board[58] != 0 || board[57] != 0)
        {
          return {};
        }
        if (isSquareControled(59) != -1 || isSquareControled(58) != -1)
        {
          return {};
        }
        return {Move::Move(4, 2, Move::PieceType::KING, {Move::MoveTypes::LONG_CASTLE})};
      }
    }

    bool isCapture = std::find(move.moveTypes.begin(), move.moveTypes.end(), Move::MoveTypes::CAPTURE) != move.moveTypes.end();

    int from = checkKingMoves(move.to);

    if (from == -1)
    {
      return {};
    }

    if (isCapture)
    {
      if (isWhiteTurn)
      {
        if (!(board[move.to] & 1))
          return {};
      }
      else
      {
        if ((!board[move.to] && board[move.to] & 0))
          return {};
      }
    }
    else
    {
      if (board[move.to] != 0)
        return {};
    }

    if (isWhiteTurn)
    {
      if (board[from] != 64)
        return {};
    }
    else
    {
      if (board[from] != 65)
        return {};
    }

    return {Move::Move(from, move.to, Move::PieceType::KING, {})};
  }

  std::pair<bool, Move::Move> Board::checkForPromotion(const Move::Move &move)
  {
    int targetSquare = move.to;

    if (std::find(move.moveTypes.begin(), move.moveTypes.end(), Move::MoveTypes::CAPTURE) != move.moveTypes.end())
    {
      if (std::find(move.moveTypes.begin(), move.moveTypes.end(), Move::MoveTypes::PROMOTION) != move.moveTypes.end() || targetSquare >= 56 || targetSquare <= 7)
      {
        if (isWhiteTurn)
        {
          if (targetSquare >= 56)
          {
            if (move.promotionTo == -1)
            {
              return {true, Move::Move(false)};
            }
            else
            {
              Move::Move result = Move::Move(true);

              if (targetSquare >= 7 && board[targetSquare + Board::DOWN_RIGHT] == Board::PAWN && !isOnRightBorder(targetSquare))
              {
                result = Move::Move(targetSquare + Board::DOWN_RIGHT, targetSquare, Move::PieceType::PAWN, {Move::MoveTypes::CAPTURE, Move::MoveTypes::PROMOTION});
              }
              else if (targetSquare >= 9 && board[targetSquare + Board::DOWN_LEFT] == Board::PAWN && !isOnLeftBorder(targetSquare))
              {
                result = Move::Move(targetSquare + Board::DOWN_LEFT, targetSquare, Move::PieceType::PAWN, {Move::MoveTypes::CAPTURE, Move::MoveTypes::PROMOTION});
              }
              else
              {
                return {true, Move::Move(false)};
              }

              result.promotionTo = move.promotionTo;
              return {true, result};
            }
          }
          else
          {
            return {true, Move::Move(false)};
          }
        }
        else
        {
          if (targetSquare <= 7)
          {
            if (move.promotionTo == -1)
            {
              return {true, Move::Move(false)};
            }
            else
            {
              Move::Move result = Move::Move(true);

              if (targetSquare <= 56 && board[targetSquare + Board::UP_LEFT] == (Board::COLOR | Board::PAWN) && !isOnLeftBorder(targetSquare))
              {
                result = Move::Move(targetSquare + Board::UP_LEFT, targetSquare, Move::PieceType::PAWN, {Move::MoveTypes::CAPTURE, Move::MoveTypes::PROMOTION});
              }
              else if (targetSquare <= 54 && board[targetSquare + Board::UP_RIGHT] == (Board::COLOR | Board::PAWN) && !isOnRightBorder(targetSquare))
              {
                result = Move::Move(targetSquare + Board::UP_RIGHT, targetSquare, Move::PieceType::PAWN, {Move::MoveTypes::CAPTURE, Move::MoveTypes::PROMOTION});
              }
              else
              {
                return {true, Move::Move(false)};
              }

              result.promotionTo = move.promotionTo;
              return {true, result};
            }
          }
          else
          {
            return {true, Move::Move(false)};
          }
        }
      }
    }
    else
    {
      if (isWhiteTurn)
      {
        // Checkk for promotion
        if (std::find(move.moveTypes.begin(), move.moveTypes.end(), Move::MoveTypes::PROMOTION) != move.moveTypes.end() || targetSquare >= 56)
        {
          if (targetSquare >= 56)
          {
            if (move.promotionTo == -1)
            {
              return {true, Move::Move(false)};
            }
            else
            {
              Move::Move result = Move::Move(true);

              result = Move::Move(targetSquare + Board::DOWN, targetSquare, Move::PieceType::PAWN, {Move::MoveTypes::PROMOTION});

              result.promotionTo = move.promotionTo;
              return {true, result};
            }
          }
          else
          {
            return {true, Move::Move(false)};
          }
        }
      }
      else
      {
        // Check for promotion
        if (std::find(move.moveTypes.begin(), move.moveTypes.end(), Move::MoveTypes::PROMOTION) != move.moveTypes.end() || targetSquare <= 7)
        {
          if (targetSquare <= 7)
          {
            if (move.promotionTo == -1)
            {
              return {true, Move::Move(false)};
            }
            else
            {
              Move::Move result = Move::Move(true);

              result = Move::Move(targetSquare + Board::UP, targetSquare, Move::PieceType::PAWN, {Move::MoveTypes::PROMOTION});

              result.promotionTo = move.promotionTo;
              return {true, result};
            }
          }
          else
          {
            return {true, Move::Move(false)};
          }
        }
      }
    }

    return {false, Move::Move(false)};
  }

  std::pair<bool, Move::Move> Board::checkForEnPassant(const Move::Move &move)
  {
    if (moveHistory.size() == 0)
    {
      return {false, Move::Move(false)};
    }

    int targetSquare = move.to;

    Move::Move lastMove = moveHistory.back();

    if (isWhiteTurn)
    {
      if (lastMove.pieceType == Move::PieceType::PAWN && lastMove.to == targetSquare + Board::DOWN && lastMove.from == targetSquare + Board::UP && board[lastMove.to + Board::LEFT] == Board::PAWN && !isOnLeftBorder(targetSquare))
      {
        return {true, Move::Move(targetSquare + Board::DOWN_LEFT, targetSquare, Move::PieceType::PAWN, {Move::MoveTypes::CAPTURE, Move::MoveTypes::EN_PASSANT})};
      }
      else if (lastMove.pieceType == Move::PieceType::PAWN && lastMove.to == targetSquare + Board::DOWN && lastMove.from == targetSquare + Board::UP && board[lastMove.to + Board::RIGHT] == Board::PAWN && !isOnRightBorder(targetSquare))
      {
        return {true, Move::Move(targetSquare + Board::DOWN_RIGHT, targetSquare, Move::PieceType::PAWN, {Move::MoveTypes::CAPTURE, Move::MoveTypes::EN_PASSANT})};
      }
    }
    else
    {
      if (lastMove.pieceType == Move::PieceType::PAWN && lastMove.to == targetSquare + Board::UP && lastMove.from == targetSquare + Board::DOWN && board[lastMove.to + Board::LEFT] == (Board::PAWN | Board::COLOR) && !isOnLeftBorder(targetSquare))
      {
        return {true, Move::Move(targetSquare + Board::UP_LEFT, targetSquare, Move::PieceType::PAWN, {Move::MoveTypes::CAPTURE, Move::MoveTypes::EN_PASSANT})};
      }
      else if (lastMove.pieceType == Move::PieceType::PAWN && lastMove.to == targetSquare + Board::UP && lastMove.from == targetSquare + Board::DOWN && board[lastMove.to + Board::RIGHT] == (Board::PAWN | Board::COLOR) && !isOnRightBorder(targetSquare))
      {
        return {true, Move::Move(targetSquare + Board::UP_RIGHT, targetSquare, Move::PieceType::PAWN, {Move::MoveTypes::CAPTURE, Move::MoveTypes::EN_PASSANT})};
      }
    }

    return {false, Move::Move(false)};
  }

  inline bool Board::isOnRightBorder(int square)
  {
    return square % 8 == 7;
  }

  inline bool Board::isOnLeftBorder(int square)
  {
    return square % 8 == 0;
  }

  inline bool Board::isOnTopBorder(int square)
  {
    return square >= 0 && square <= 7;
  }

  inline bool Board::isOnBottomBorder(int square)
  {
    return square >= 56 && square <= 63;
  }

  int Board::checkDiagonal(int square, Move::PieceType type, bool isCapture, bool reverseColor)
  {

    int offsets[] = {Board::UP_RIGHT, Board::DOWN_RIGHT, Board::DOWN_LEFT, Board::UP_LEFT};

    for (int offset : offsets)
    {
      for (int i = square; i >= 0 && i < 64; i += offset)
      {
        if (board[i] == (type | (reverseColor ? isWhiteTurn : !isWhiteTurn)))
        {
          return i;
        }
        else if ((!isCapture && board[i] != 0) || (isCapture && board[i] != 0 && i != square))
        {
          break;
        }
      }
    }

    return -1;
  }

  std::vector<int> Board::checkVerticalAndHorizontal(int square, Move::PieceType type, bool isCapture, bool reverseColor)
  {
    std::vector<int> results = {};
    int offsets[] = {Board::UP, Board::RIGHT, Board::DOWN, Board::LEFT};

    for (int offset : offsets)
    {
      for (int i = square; i >= 0 && i < 64; i += offset)
      {
        std::cout << "i: " << i << " | board[i]: " << board[i] << std::endl;
        if (board[i] == (type | (reverseColor ? isWhiteTurn : !isWhiteTurn)))
        {
          results.push_back(i);
          break;
        }
        else if ((!isCapture && board[i] != Board::NONE) || (isCapture && board[i] != Board::NONE && i != square))
        {
          break;
        }
      }
    }

    return results;
  }

  std::vector<std::pair<int, bool>> Board::getDiagonalMoves(int square)
  {
    std::vector<std::pair<int, bool>> results = {};
    int offsets[] = {Board::UP_RIGHT, Board::DOWN_RIGHT, Board::DOWN_LEFT, Board::UP_LEFT};

    for (int offset : offsets)
    {
      for (int i = square; i >= 0 && i < 64; i += offset)
      {
        if (i == square)
          continue;
        if (checkIfCrossesBorder(i, i - offset))
          break;
        if (board[i] != Board::NONE)
        {
          if (isWhiteTurn && (board[i] & !Board::COLOR) || !isWhiteTurn && (board[i] & Board::COLOR))
            break;
          else if (isWhiteTurn && (board[i] & Board::COLOR) || !isWhiteTurn && (board[i] & !Board::COLOR))
          {
            results.push_back({i, true});
            break;
          }
          else
          {
            break;
          }
        }
        else
        {
          results.push_back({i, false});
        }
      }
    }

    return results;
  }

  std::vector<std::pair<int, bool>> Board::getVerticalAndHorizontalMoves(int square)
  {
    std::vector<std::pair<int, bool>> results = {};
    int offsets[] = {Board::UP, Board::RIGHT, Board::DOWN, Board::LEFT};

    for (int offset : offsets)
    {
      for (int i = square; i >= 0 && i < 64; i += offset)
      {
        if (i == square)
          continue;
        if (checkIfCrossesBorder(i, i - offset))
          break;
        if (board[i] != Board::NONE)
        {
          if (isWhiteTurn && (board[i] & !Board::COLOR) || !isWhiteTurn && (board[i] & Board::COLOR))
            break;
          else if (isWhiteTurn && (board[i] & Board::COLOR) || !isWhiteTurn && (board[i] & !Board::COLOR))
          {
            results.push_back({i, true});
            break;
          }
          else
          {
            break;
          }
        }
        else
        {
          results.push_back({i, false});
        }
      }
    }

    return results;
  }

  std::vector<int> Board::checkKnightMoves(int square, bool reverseColor)
  {
    std::vector<int> results = {};
    int offsets[] = {6, 10, 15, 17, -6, -10, -15, -17};
    for (int offset : offsets)
    {
      int target = square + offset;
      if (target >= 0 && target < 64 && square >= 0 && square < 64 && board[target] == (Board::KNIGHT | (reverseColor ? isWhiteTurn : !isWhiteTurn)))
      {
        results.push_back(target);
      }
    }
    return results;
  }

  int Board::checkKingMoves(int square)
  {
    int offsets[] = {Board::UP, Board::UP_RIGHT, Board::RIGHT, Board::DOWN_RIGHT, Board::DOWN, Board::DOWN_LEFT, Board::LEFT, Board::UP_LEFT};

    for (int offset : offsets)
    {
      int target = square + offset;
      if (target >= 0 && target < 64 && board[target] == (64 | (!isWhiteTurn)))
      {
        for (int offset2 : offsets)
        {
          int target2 = target + offset2;
          if (target2 >= 0 && target2 < 64 && board[target2] == (64 | (isWhiteTurn)))
          {
            return target2;
            break;
          }
        }
        return target;
        break;
      }
    }

    return -1;
  }

  int Board::isSquareControled(int square)
  {
    // int bishop = checkDiagonal(square, Move::PieceType::BISHOP, false, true);
    // if (bishop != -1)
    //   return bishop;
    // int rook = checkVerticalAndHorizontal(square, Move::PieceType::ROOK, false, true);
    // if (rook != -1)
    //   return rook;
    // int queen = checkVerticalAndHorizontal(square, Move::PieceType::QUEEN, false, true);
    // if (queen == -1)
    //   queen = checkDiagonal(square, Move::PieceType::QUEEN, false, true);
    // if (queen != -1)
    //   return queen;
    // int knight = checkKnightMoves(square, true);
    // if (knight != -1)
    //   return knight;
    // int king = checkKingMoves(square);
    // if (king != -1)
    //   return king;
    return -1;
  }

  bool Board::makeShortCastle()
  {
    if (isWhiteTurn)
    {
      board[4] = Board::NONE;
      board[5] = Board::ROOK;
      board[6] = Board::KING;
      board[7] = Board::NONE;
      hasWhiteKingMoved = true;
      hasWhiteRookHMoved = true;
      currentWhiteKingPosition = 6;
    }
    else
    {
      board[60] = Board::NONE;
      board[61] = Board::COLOR | Board::ROOK;
      board[62] = Board::COLOR | Board::KING;
      board[63] = Board::NONE;
      hasBlackKingMoved = true;
      hasBlackRookHMoved = true;
      currentBlackKingPosition = 62;
    }
    isWhiteTurn = !isWhiteTurn;
    return true;
  }

  bool Board::makeLongCastle()
  {
    if (isWhiteTurn)
    {
      board[4] = Board::NONE;
      board[3] = Board::ROOK;
      board[2] = Board::KING;
      board[1] = Board::NONE;
      board[0] = Board::NONE;
      hasWhiteKingMoved = true;
      hasWhiteRookAMoved = true;
      currentWhiteKingPosition = 2;
    }
    else
    {
      board[60] = Board::NONE;
      board[59] = Board::COLOR | Board::ROOK;
      board[58] = Board::COLOR | Board::KING;
      board[57] = Board::NONE;
      board[56] = Board::NONE;
      hasBlackKingMoved = true;
      hasBlackRookAMoved = true;
      currentBlackKingPosition = 58;
    }
    isWhiteTurn = !isWhiteTurn;
    return true;
  }

  bool Board::makeRegularMove(const Move::Move &move)
  {

    board[move.from] = Board::NONE;
    board[move.to] = move.pieceType | (!isWhiteTurn);

    if (isWhiteTurn)
    {
      if (isSquareControled(currentBlackKingPosition) != -1)
      {
        board[move.from] = move.pieceType | (!isWhiteTurn);
        board[move.to] = Board::NONE;
        return false;
      }
    }
    else
    {
      if (isSquareControled(currentWhiteKingPosition) != -1)
      {
        board[move.from] = move.pieceType | (!isWhiteTurn);
        board[move.to] = Board::NONE;
        return false;
      }
    }

    if (std::find(move.moveTypes.begin(), move.moveTypes.end(), Move::MoveTypes::EN_PASSANT) != move.moveTypes.end())
    {
      if (isWhiteTurn)
      {
        board[move.to + Board::DOWN] = Board::NONE;
      }
      else
      {
        board[move.to + Board::UP] = Board::NONE;
      }
    }

    if (std::find(move.moveTypes.begin(), move.moveTypes.end(), Move::MoveTypes::PROMOTION) != move.moveTypes.end())
    {
      board[move.to] = move.promotionTo | (!isWhiteTurn);
    }

    return true;
  }

  bool Board::checkIfCrossesBorder(int square1, int square2)
  {
    return (abs(square1 / 8 - square2 / 8) > 1) || (abs(square1 % 8 - square2 % 8) > 1);
  }

  int Board::getSquare(std::string square)
  {
    return square[0] - 'a' + (square[1] - '1') * 8;
  }
}