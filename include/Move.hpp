#ifndef MOVE_HPP
#define MOVE_HPP

#include <string>
#include <vector>

namespace Move
{
  enum PieceType
  {
    NONE = 0,
    PAWN = 2,
    KNIGHT = 4,
    BISHOP = 8,
    ROOK = 16,
    QUEEN = 32,
    KING = 64
  };

  enum MoveTypes
  {
    CHECK,
    CHECKMATE,
    CAPTURE,
    PROMOTION,
    SHORT_CASTLE,
    LONG_CASTLE,
    EN_PASSANT
  };

  class Move
  {
  public:
    // Type of piece that was moved
    PieceType pieceType;

    // An optional argument to specify the starting file or rank of the piece being moved if the move is ambiguous
    int from = -1;

    // The square the piece is moving to
    int to;

    // The type of move
    std::vector<MoveTypes> moveTypes;

    bool isVaild = true;
    int promotionTo = -1;

    // Move(PieceType pieceType, char from, char to[]);
    Move(const std::string &move);
    Move(int from, int to, PieceType pieceType, std::vector<MoveTypes> moveTypes);
    Move(int from, int to, PieceType pieceType, std::vector<MoveTypes> moveTypes, PieceType promotionTo);
    Move(bool isValid);
    void setPieceType(const std::string &move);
    void check_and_set_castle(const std::string &move);
    int getSquareIndex(const std::string &move);
    std::string toString() const;
  };
} // namespace Move

#endif // MOVE_HPP